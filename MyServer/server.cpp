#include "server.h"
#include "ui_server.h"
#include "question.h"
#include "questionbank.h"
#include <QNetworkProxyFactory>
#include <QTime>

QString Server::add(QString text,qint32 qid)
{
    Question* ques = questionbank->GetQuestion(qid);
    text.append(ques->GetID());
    text.append("+");
    text.append(ques->GetDescript());
    text.append("+");
    text.append(ques->GetOption(A));
    text.append("+");
    text.append(ques->GetOption(B));
    text.append("+");
    text.append(ques->GetOption(C));
    text.append("+");
    text.append(ques->GetOption(D));
    text.append("+");
    text.append(ques->GetAnswer());

    return text;
}

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    server = new QTcpServer();
    client_num = 0;
    questionbank = new QuestionBank();
    userbank = new UserBank();

    if(!server->listen(QHostAddress::Any,6666))
    {
        //若出错，则输出错误信息
        qDebug()<<server->errorString();
        return;
    }
    qDebug()<< "Listen succeessfully!";
    //连接信号槽
    connect(server,&QTcpServer::newConnection,this,&Server::server_New_Connect);
}

Server::~Server()
{
    server->close();
    server->deleteLater();
    delete ui;
}

bool Server::test(QString ID, QString res)
{
    quint32 qid = ID.toInt();
    Question* ques = questionbank->GetQuestion(qid);
    if(ques->GetAnswer() == res)return true;
    else return false;
}

QList<qint32> Server::generateUniqueRandNumbers(qint32 MAXNUM, qint32 queNum) {
    QList<qint32> numbersList;
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    for (qint32 i = 0; i < queNum; i++) {
        numbersList.append(qrand() % MAXNUM);

        while (true) {
            qint32 j;
            for (j = 0; j < i; j++) {
                if (numbersList[i] == numbersList[j])
                    break;
            }
            if (j < i) {
                numbersList[i] = rand() % MAXNUM;
                continue;
            } else if (j == i) {
                break;
            }
        }
    }

    std::sort(numbersList.begin(), numbersList.end());
    for (qint32 i = 0; i < queNum; i++)
        qDebug() << numbersList[i];

    return numbersList;
}

bool Server::find_ID(QString ID)
{
    User* user = userbank->getUser(ID);
    if(user)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Server::match_ID_password(QString ID, QString password)
{
    User* user = userbank->getUser(ID);
    qDebug() << user->name << " " << user->password;
    if(user && user->password == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Server::server_New_Connect()
{
    if(client_num<2)client_num++;
    if(client_num==1)
    {
        //获取客户端连接
        socket1 = server->nextPendingConnection();
        //连接QTcpSocket的信号槽，以读取新数据
        QObject::connect(socket1, &QTcpSocket::readyRead, this, &Server::socket_Read_Data1);
        QObject::connect(socket1, &QTcpSocket::disconnected, this, &Server::socket_Disconnected1);
        qDebug() << "A Client connect!";
    }
    else if(client_num==2)
    {
        //获取客户端连接
        socket2 = server->nextPendingConnection();
        //连接QTcpSocket的信号槽，以读取新数据
        QObject::connect(socket2, &QTcpSocket::readyRead, this, &Server::socket_Read_Data2);
        QObject::connect(socket2, &QTcpSocket::disconnected, this, &Server::socket_Disconnected2);
        qDebug() << "B Client connect!";
    }
}

void Server::socket_Read_Data1()
{
    QByteArray buffer;
    QString data;
    //读取缓冲区数据
    buffer = socket1->readAll();
    //data = QString::fromLocal8Bit(buffer);
    data = buffer;
    qDebug()<<data;
    QStringList list=data.split(",");//所有独立的信息都以“,”分隔
    QString text;
    if(list[0] == "a")//登录信息
    {
        text.append("a,");
        //查询ID与password是否匹配，list[1]是ID，list[2]是密码。
        qDebug()<<list[1];
        qDebug()<<list[2];
        bool res = match_ID_password(list[1],list[2]);
        if(res == true)
        {
            //匹配的话，就可以进入登录成功，发送登录成功提示
            text.append("s");
        }
        else
        {
            //不匹配的话，发送登录失败提示
            text.append("f");
        }
        qDebug()<<text;
        socket1->write(text.toUtf8());
    }
    else if(list[0]=="b")//注册信息
    {
        text.append("b,");
        //查询用户ID是否已经存在
        bool res = find_ID(list[1]);
        if(res == true)
        {
            //如果已经存在，提示重新输入
            text.append("f");
        }
        else
        {
            //如果不存在，则将用户账号信息保存至文件，并发送注册成功的信号
            User* user = new User();
            user->name = list[1];
            user->password = list[2];
            if(userbank->addUser(user))
                text.append("s");
            else text.append("f");
        }
        qDebug()<<text;
        socket1->write(text.toUtf8());
    }
    else if(list[0]=="c")//接收客户的回答
    {
        text.append("c,");
        //接受客户的回答，并查询答案的正误
        bool res = test(list[1],list[2]);//list[1]放题号,list[2]放回答
        if(res == true)
        {
            //如果回答正确
            //text.append("t");
        }
        else
        {
            //如果回答错误
            //text.append("f");
        }
    }
    else if(list[0]=="d")//接收客户的单机游戏信号
    {
        //给用户发送题目,题目号随机per_num个
        QList<qint32> qlist = generateUniqueRandNumbers(max_num,per_num);
        text.append("d,");
        text.append(QString::number(per_num,10));
        text.append(";");
        for(int i=0;i<qlist.size();i++)
        {
            text = add(text,qlist[i]);
            if(i<qlist.size()-1)text.append(";");
        }
        qDebug()<<text;
        socket1->write(text.toUtf8());
    }
    else if(list[0]=="e")//接收客户的匹配游戏信号
    {
        //给用户随机分配一个对手，给用户发送对手信息
        //给用户发送题目编号
        text.append("e,");
        text.append(QString::number(per_num,10));
        //加入对手信息
        QList<qint32> qlist = generateUniqueRandNumbers(max_num,per_num);
        for(int i=0;i<qlist.size();i++)
        {
            text = add(text,qlist[i]);
            if(i<qlist.size()-1)text.append(",");
        }
        qDebug()<<text;
        socket1->write(text.toUtf8());
    }
}

void Server::socket_Read_Data2()
{
    QByteArray buffer;
    QString data;
    //读取缓冲区数据
    buffer = socket2->readAll();
    //data = QString::fromLocal8Bit(buffer);
    data = buffer;
    qDebug()<<data;
    QStringList list=data.split(",");//所有独立的信息都以“,”分隔
    if(list[0] == "a")//登录信息
    {
        QString text;
        text.append("a,");
        //查询ID与password是否匹配，list[1]是ID，list[2]是密码。
        bool res = match_ID_password(list[1],list[2]);
        if(res == true)
        {
            //匹配的话，就可以进入登录成功，发送登录成功提示
            text.append("s");
        }
        else
        {
            //不匹配的话，发送登录失败提示
            text.append("f");
        }
        socket2->write(text.toLocal8Bit());
    }
    else if(list[0]=="b")//注册信息
    {
        QString text;
        text.append("b,");
        //查询用户ID是否已经存在
        bool res = find_ID(list[1]);
        if(res == true)
        {
            //如果已经存在，提示重新输入
            text.append("f");
        }
        else
        {
            //如果不存在，则将用户账号信息保存至文件，并发送注册成功的信号
            User* user = new User();
            user->name = list[1];
            user->password = list[2];
            if(userbank->addUser(user))
                text.append("s");
            else text.append("f");
        }
        socket2->write(text.toLocal8Bit());
    }
    else if(list[0]=="c")//接收客户的回答
    {
        QString text;
        text.append("c,");
        //接受客户的回答，并查询答案的正误
        bool res = test(list[1],list[2]);//list[1]放题号,list[2]放回答
        if(res == true)
        {
            //如果回答正确
            text.append("t");
        }
        else
        {
            //如果回答错误
            text.append("f");
        }
        socket2->write(text.toLocal8Bit());
    }
    else if(list[0]=="d")//接收客户的单机游戏信号
    {
        //给用户发送题目,题目号随机per_num个
        QList<qint32> qlist = generateUniqueRandNumbers(max_num,per_num);
        QString text;
        text.append("d,");
        text.append(QString::number(per_num,10));
        for(int i=0;i<qlist.size();i++)
        {
            text = add(text,qlist[i]);
            if(i<qlist.size()-1)text.append(";");
        }
        socket2->write(text.toLocal8Bit());
    }
    else if(list[0]=="e")//接收客户的匹配游戏信号
    {
        //给用户随机分配一个对手，给用户发送对手信息
        //给用户发送题目编号
        QString text;
        text.append("e,");
        text.append(QString::number(per_num,10));
        //加入对手信息
        QList<qint32> qlist = generateUniqueRandNumbers(max_num,per_num);
        for(int i=0;i<qlist.size();i++)
        {
            text = add(text,qlist[i]);
            if(i<qlist.size()-1)text.append(",");
        }
        socket2->write(text.toLocal8Bit());
    }
}

void Server::socket_Disconnected1()
{
    qDebug() << "Client A disconnected!";
    client_num--;
}

void Server::socket_Disconnected2()
{
    qDebug() << "Client B disconnected!";
    client_num--;
}
