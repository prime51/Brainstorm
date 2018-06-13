//#ifndef SERVER_H
//#define SERVER_H

//#include <QWidget>
//#include <QList>

//namespace Ui {
//class Server;
//}

//class Server : public QWidget
//{
//    Q_OBJECT

//public:

//    //构造函数
//    explicit Server(QWidget *parent = 0);

//    //析构函数
//    ~Server();

//private:
//    Ui::Server *ui;
//    QTcpServer *_tcpServer;
//    QTcpSocket *_tcpSocket;
//    QList<QTcpSocket *> Socket_list;

//    QVector<QTcpSocket *> PKSocket;     // 保存 匹配列表中的 客户端的 SOCKET

//    QMap<QString, QTcpSocket*> Online;  // 在线用户信息

//    Recv sendToClient1, sendToClient2;

//public slots:

//    // 接受客户端连接
//    void acceptClient();

//    // 监听用户发出的信息
//    void acceptmessage();

//    // 监听客户端操作
//    void acceptop();

//    //接受客户端的注册信息
//    void rec_register_info(QTcpSocket *client_Socket);

//    //接受客户端的登录信息
//    void rec_login_info(QTcpSocket *client_Socket);

//    //接受客户端的回答
//    void rec_response(QTcpSocket *client_Socket);

//    //给客户端发送题目信息
//    void send_question(QTcpSocket *client_Socket);

//    //给客户端反馈答题结果
//    void send_result(QTcpSocket *client_Socket);

//    //随机匹配对手
//    void random_match(QTcpSocket *client_Socket);
//};

//#endif // SERVER_H

//server.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private slots:
    void on_pushButton_Listen_clicked();

    void on_pushButton_Send_clicked();

    void server_New_Connect();

    void socket_Read_Data1();

    void socket_Read_Data2();

    void socket_Disconnected();

private:
    Ui::Server *ui;
    QTcpServer* server;
    QTcpSocket* socket1;
    QTcpSocket* socket2;
    quint16 client_num;
};

#endif // MAINWINDOW_H
