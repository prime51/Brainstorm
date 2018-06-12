//widget.h
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>   // tcp服务器类
#include <QTcpSocket>   // 套接字类
#include "Mythread.h"
#include <QVector>
#include <QMap>
#include <QMutex>

class Widget;

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

    void timerEvent(QTimerEvent *event);

    QString SearchForName(QTcpSocket *client);

    // 由客户端传递过来的 对手的 昵称 ，找到对应的 socket
    QTcpSocket* SearchForSocket(QString name);
public slots:
    // 接受客户端连接
    void acceptClient();

    // 接受客户端成功登陆信息，保存到在线用户容器中
    void rec_user_info(QString name, QTcpSocket* client);

    // 接受客户端发送匹配申请的信息
    void rec_client_match_soket(QTcpSocket *client_Socket);

    // 接受客户端转发的分数，实现同步显示
    void rec_tran_score(QTcpSocket* client, int score, QString name);

    // 接收客户端发送的答题结果，更新数据库信息
    void rec_match_result(QTcpSocket* client, int score);

    // 接收客户端退出的请求信号
    void Remove_client(QTcpSocket* client);

private:
    Ui::Widget *ui;

    QTcpServer *_tcpServer;
    QTcpSocket *_tcpSocket;

    QVector<QTcpSocket *> PKSocket;     // 保存 匹配列表中的 客户端的 SOCKET
                                        // 匹配成功后，删除 这两个套接字

    QMap<QString, QTcpSocket*> Online;  // 在线用户信息

    Recv sendToClient1, sendToClient2;

    int timeID;
    QMutex mutex;

    QSqlDatabase db;            // 数据库句柄
};

#endif // WIDGET_H
