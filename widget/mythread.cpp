// mythread.cpp

#include "Mythread.h"
#include <QObject>
#include <QDebug>
#include <QTimerEvent>
#include <QTime>

Mythread::Mythread(QTcpSocket *client, QObject *parent) : QThread(parent)
{
    //connect(client, SIGNAL(readyRead()), this, SLOT(dealClientData()));
    this->client = client;
    num   = 0;
    count = -1;
}

void Mythread::run()
{
    connect(client, SIGNAL(readyRead()), this, SLOT(dealClientData()));
    qDebug() << "新的线程";
}

void Mythread::dealClientData()
{
    QDataStream in(client);
    blocksize = 0;
    if(blocksize == 0)
    {
        if(client->bytesAvailable() < (int)sizeof(qint16))
        {
            return;
        }
        in >> blocksize;
    }
    if(client->bytesAvailable() < blocksize)
    {
        return;
    }

    in >> Rec_msg;

    qDebug() << "11111" <<Rec_msg.cmd;
    qDebug() << "Enemy name" << Rec_msg.EnemyName;

    switch (Rec_msg.cmd) {
    case REGISTER:
        user_Register();
        break;
    case LOGIN:
        user_Login();
        break;
    case MATCHING:
        user_match();
        break;
    case GAMEING:
        sendQues();
        break;
    case TRANSMIT:
        emit send_trans_score(client, Rec_msg.total, Rec_msg.EnemyName);
        break;
    case MATCHRESULT:
        emit send_match_result(client, Rec_msg.total);
        break;
    case QUIT:
        emit removeFromMap(client);
        break;
    default:
        break;
    }
}

/*
 * 往数据库中添加注册信息
 */
void Mythread::user_Register()
{

    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("123456");
    this->db.setDatabaseName("question_bank");

    bool ok = db.open();
    if(ok)
    {
        qDebug() <<"open database success";
    }
    else
    {
        qDebug() <<"open database error";
    }


    QSqlQuery query;

    Rec_msg.level  = "无段位";
    query.prepare("INSERT INTO user_info VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(Rec_msg.name.toUtf8());
    query.addBindValue(Rec_msg.passwd);
    query.addBindValue(Rec_msg.tele);
    query.addBindValue(0);
    query.addBindValue(Rec_msg.level.toUtf8());

    query.exec();

    db.close();
}

/*
 * 验证登录信息
 */
void Mythread::user_Login()
{
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("123456");
    this->db.setDatabaseName("question_bank");

    bool ok = db.open();
    if(ok)
    {
        qDebug() <<"open database success";
    }
    else
    {
        qDebug() <<"open database error";
    }


    QSqlQuery query;
    qDebug() << Rec_msg.name << Rec_msg.passwd;

    query.prepare("select *from user_info");
    query.exec();

    bool Flag = false;

    while(query.next())
    {
        if(query.value(0).toString().toLocal8Bit() == Rec_msg.name
                && query.value(1).toString() == Rec_msg.passwd)
        {
            Flag = true;
            Rec_msg.level = query.value(4).toString().toLocal8Bit();
            Rec_msg.total = query.value(3).toInt();
            break;
        }
    }

    if(Flag)
    {
//        qDebug() <<"Flag == true";
        Rec_msg.cmd = ALLOWLOGIN;

        qDebug() << Rec_msg.level;
        qDebug() << Rec_msg.total;

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out<<(qint16)0;
        out<<Rec_msg;
        out.device()->seek(0);
        out<<(qint16)(block.size() - sizeof(qint16));
        client->write(block, block.length());

        emit send_user_info(Rec_msg.name, client);
    }
    else
    {
        Rec_msg.cmd = REFUSELOGIN;
        qDebug() <<"Flag == false";
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out<<(qint16)0;
        out<<Rec_msg;
        out.device()->seek(0);
        out<<(qint16)(block.size() - sizeof(qint16));
        client->write(block, block.length());
    }

    db.close();

}

/*
 * 客户端申请匹配
 */
void Mythread::user_match()
{
   emit client_match_socket(client);
}

/*
 * 向用户分发题目
 * 一次性将所有题目抽取出来，放在容器内，利用定时器控制分发不同的题
 */
void Mythread::sendQues()
{
    int arr[20] = {0};
    int length = 20;

    for(int i = 0; i < 20; i++)
    {
        arr[i] = i + 1;
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 0; i < length - 1; i++)
    {
        int index = qrand()%(length-i);

        int tmp = arr[index];
        arr[index] = arr[length-i-1];
        arr[length-i-1] = tmp;
    }

    this->db = QSqlDatabase::addDatabase("QMYSQL");
    this->db.setHostName("localhost");
    this->db.setUserName("root");
    this->db.setPassword("123456");
    this->db.setDatabaseName("question_bank");

    bool ok = db.open();
    if(ok)
    {
        qDebug() <<"open database success";
    }
    else
    {
        qDebug() <<"open database error";
    }


    for(int i = 1; i < 6; i++)
    {
        QSqlQuery query;
        query.prepare("select *from question where ID = ?");
        query.addBindValue(arr[i]);
        query.exec();
        query.next();

        ques.push_back(QString(query.value(1).toString()));
        answer1.push_back(QString(query.value(2).toString()));
        answer2.push_back(QString(query.value(3).toString()));
        answer3.push_back(QString(query.value(4).toString()));
        correct.push_back(query.value(5).toInt());
    }

    db.close();

    timeID = startTimer(1000);
}

void Mythread::timerEvent(QTimerEvent *event)
{
    // 5秒 一题，第一次发题目时，触发客户端的计时器，让客户端进行答题界面
    // 第二次及以后的发题，不再触发客户端的计时器，仅仅是将题目添加到客户端的容器中
    if(num++ % 5 == 0 && count != 4)
    {
        ++count;

        if(count == 0)
            Rec_msg.cmd     = FIRSTONGAMESTAT;
        else
            Rec_msg.cmd     = OTHERONAGMESTAT;

        Rec_msg.ques    = ques.at(count).toLocal8Bit();
        Rec_msg.answer1 = answer1.at(count).toLocal8Bit();
        Rec_msg.answer2 = answer2.at(count).toLocal8Bit();
        Rec_msg.answer3 = answer3.at(count).toLocal8Bit();
        Rec_msg.correct = correct.at(count);

        qDebug() << Rec_msg.ques;
        qDebug() << Rec_msg.answer1;
        qDebug() << Rec_msg.answer2;
        qDebug() << Rec_msg.answer3;
        qDebug() << Rec_msg.correct;

        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out<<(qint16)0;
        out<<Rec_msg;
        out.device()->seek(0);
        out<<(qint16)(block.size() - sizeof(qint16));
        client->write(block, block.length());
    }

    if(count == 4)
    {
        killTimer(timeID);
        count = -1;
        num = 0;
        for(int i = 0; i < 5 ; i++)
        {
            ques.pop_back();
            answer1.pop_back();
            answer2.pop_back();
            answer3.pop_back();
            correct.pop_back();
        }
    }
}
