//widget.cpp

#include "widget.h"
#include "ui_widget.h"
#include "Mythread.h"
#include <QTime>
#include <QTimerEvent>
#include <QMutexLocker>
#include <QMap>
#include <iterator>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 创建服务器
    _tcpServer = new QTcpServer(this);

    // 监听ip 地址和端口
    _tcpServer->listen(QHostAddress::Any, 9999);

    // 等待客户端连接
    connect (_tcpServer, SIGNAL(newConnection()), this, SLOT(acceptClient()));

    timeID = startTimer(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::acceptClient()
{
    // 因为可能有多个一起连接，要处理所有的客户端
    while (_tcpServer->hasPendingConnections())
    {
        // 接受客户端连接
        QTcpSocket *client_pthread = _tcpServer->nextPendingConnection();
        Mythread *pthread = new Mythread(client_pthread, this);

    connect(pthread, SIGNAL(send_user_info(QString,QTcpSocket*)), this, SLOT(rec_user_info(QString,QTcpSocket*)));

    connect(pthread, SIGNAL(client_match_socket(QTcpSocket*)),this, SLOT(rec_client_match_soket(QTcpSocket*)), Qt::QueuedConnection);

    connect(pthread, SIGNAL(send_trans_score(QTcpSocket*,int,QString)), this, SLOT(rec_tran_score(QTcpSocket*,int,QString)));

    connect(pthread, SIGNAL(send_match_result(QTcpSocket*,int)), this, SLOT(rec_match_result(QTcpSocket*,int)));

    connect(pthread,SIGNAL(removeFromMap(QTcpSocket*)), this, SLOT(Remove_client(QTcpSocket*)));

    pthread->start();
}

}

void Widget::rec_client_match_soket(QTcpSocket *client_Socket)
{
qDebug() <<"已添加到排位列表";
mutex.lock();
PKSocket.push_back(client_Socket);
mutex.unlock();
}

// 类似于工作在后台，一直监视数组中的人数
void Widget::timerEvent(QTimerEvent *event)
{
// 每一秒监测数组里的 客户端套接字 是否可以进行PK
// 将可以匹配的两个socket发送匹配信号后，将其清出数组
// qDebug() << PKSocket.size();
mutex.lock();
if(PKSocket.size() >= 1)
{
    /*
     *向第一个客户发送对手昵称
     */
    sendToClient1.cmd       = MATCHINGSUC;
    sendToClient1.EnemyName = Widget::SearchForName(PKSocket.at(0));

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out<<(qint16)0;
    out<<sendToClient1;
    out.device()->seek(0);
    out<<(qint16)(block.size() - sizeof(qint16));


    /*
     *向第二个客户发送对手昵称
     */
//        sendToClient2.cmd   = MATCHINGSUC;
//        sendToClient2.EnemyName = Widget::SearchForName(PKSocket.at(0));

//        QByteArray block1;
//        QDataStream out1(&block1, QIODevice::WriteOnly);
//        out1<<(qint16)0;
//        out1<<sendToClient2;
//        out1.device()->seek(0);
//        out1<<(qint16)(block1.size() - sizeof(qint16));

    PKSocket.at(0)->write(block, block.length());
    //PKSocket.at(1)->write(block1, block1.length());

    PKSocket.pop_front();
    //PKSocket.pop_front();
}
mutex.unlock();
}

// 将 昵称 与 socket 绑定插入 map 中，便于查询
void Widget::rec_user_info(QString name, QTcpSocket* client)
{
mutex.lock();
Online.insert(name, client);
mutex.unlock();
}

// 根据 socket 找到对应的 昵称
QString Widget::SearchForName(QTcpSocket *client)
{
QMap<QString, QTcpSocket*>::iterator it = Online.begin();
while(it != Online.end())
{
    if(it.value() == client)
        return it.key();
    else
        it++;
}
}

// 根据 昵称 找到对应的 socket
QTcpSocket* Widget::SearchForSocket(QString name)
{
QMap<QString, QTcpSocket*>::iterator it = Online.begin();
while(it != Online.end())
{
    if(it.key() == name)
        return it.value();
    else
        it++;
}
}

// 根据 昵称 找到对应的 socket，并将分数转发过去
void Widget::rec_tran_score(QTcpSocket* client, int score, QString name)
{
QTcpSocket *tmp         = SearchForSocket(name);
sendToClient1.cmd       = TRANSMIT;
sendToClient1.EnemyName = SearchForName(client);
sendToClient1.total     = score;

QByteArray block;
QDataStream out(&block, QIODevice::WriteOnly);
out<<(qint16)0;
out<<sendToClient1;
out.device()->seek(0);
out<<(qint16)(block.size() - sizeof(qint16));

tmp->write(block, block.length());
}

// 更新数据库的信息
void Widget::rec_match_result(QTcpSocket* client, int score)
{
QString name = SearchForName(client);
QString tmpLevel;
int tmpScore = 0;

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

//    qDebug() << "~~~~~~~~~~~~~~~~~~";
//    qDebug() << name;

QSqlQuery query;

// 先从数据库中获取之前的积分，将本次答题得分相加得到最新的积分
query.prepare("SELECT *FROM user_info  WHERE name = ? ");
query.addBindValue(name.toUtf8());
query.exec();
query.next();

tmpScore = query.value(3).toInt() + score;
qDebug() << tmpScore;

switch(tmpScore / 100)
{
    case 0:
        tmpLevel = QString("青铜");
        break;
    case 1:
        tmpLevel = QString("白银");
        break;
    case 2:
        tmpLevel = QString("黄金");
        break;
    case 3:
        tmpLevel = QString("铂金");
        break;
    case 4:
        tmpLevel = QString("钻石");
        break;
    case 5:
        tmpLevel = QString("星耀");
        break;
    case 6:
        tmpLevel = QString("王者");
        break;
     default:
        break;
}

// 更新得分和段位
query.prepare("UPDATE user_info SET level = ?, total = ? WHERE name = ?");
query.addBindValue(tmpLevel.toUtf8());
query.addBindValue(tmpScore);
query.addBindValue(name.toUtf8());
query.exec();

sendToClient1.cmd   = UPDATESCORE;
sendToClient1.level = tmpLevel;
sendToClient1.total = tmpScore;

QByteArray block;
QDataStream out(&block, QIODevice::WriteOnly);
out<<(qint16)0;
out<<sendToClient1;
out.device()->seek(0);
out<<(qint16)(block.size() - sizeof(qint16));
client->write(block, block.length());

}

// 删除退出的客户端
void Widget::Remove_client(QTcpSocket *client)
{
QMap<QString, QTcpSocket*>::iterator it = Online.begin();
while(it != Online.end())
{
    if(it.value() == client)
    {
        mutex.lock();
        Online.erase(it);
        mutex.unlock();
    }
    else
        it++;
}
}
