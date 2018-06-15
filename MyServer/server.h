//server.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QTime>
#include "question.h"
#include "questionbank.h"
#include "user.h"
#include "userbank.h"

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
    void server_New_Connect();

    void socket_Read_Data1();

    void socket_Read_Data2();

    void socket_Disconnected1();

    void socket_Disconnected2();

    bool test(QString, QString res);

    QList<qint32> generateUniqueRandNumbers(qint32 MAXNUM, qint32 queNum);

    bool match_ID_password(QString ID,QString password);

    bool find_ID(QString ID);

    QString add(QString text,qint32 qid);
private:
    Ui::Server *ui;
    QTcpServer* server;
    QTcpSocket* socket1;
    QTcpSocket* socket2;
    quint16 client_num;
    quint16 client1;
    quint16 client2;
    QuestionBank* questionbank;
    UserBank* userbank;
    const quint16 max_num = 1242;
    const quint16 per_num = 10;
};

#endif // MAINWINDOW_H
