// mythread.h
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>
#include <QtSql>

#define  REGISTER           100001
#define  LOGIN              100002
#define  ALLOWLOGIN         100003
#define  REFUSELOGIN        100004
#define  MATCHING           100005
#define  MATCHINGSUC        100006
#define  GAMEING            100007
#define  FIRSTONGAMESTAT    100008
#define  OTHERONAGMESTAT    100009
#define  TRANSMIT           100010
#define  MATCHRESULT        100011
#define  UPDATESCORE        100012
#define  QUIT               100013

struct info
{
    int cmd;
    QString name;           // 昵称
    QString passwd;         // 密码
    QString tele;           // 手机号码
    int total;              // 总分
    QString level;          // 段位

    /*
     * 问题、选项、正确答案
     */
    QString ques;
    QString answer1;
    QString answer2;
    QString answer3;
    int correct;

    QString EnemyName;
};

typedef struct info Recv;

class Mythread : public QThread
{
    Q_OBJECT
public:
    explicit Mythread(QTcpSocket *client, QObject *parent = 0);
    void run();

    void user_Register();       // 用户注册申请
    void user_Login();          // 用户登录申请
    void user_match();          // 用户匹配申请
    void sendQues();            // 向用户分发题目
                                // 重载定时器函数
    void timerEvent(QTimerEvent *event);

signals:
    void client_match_socket(QTcpSocket *client);  // 将客户端的socket发给 主窗口保存

    void send_user_info(QString name, QTcpSocket* client);

    void send_trans_score(QTcpSocket* client, int score, QString name);

    void send_match_result(QTcpSocket* client, int score);

    void removeFromMap(QTcpSocket* client);

public slots:
    void dealClientData();

private:
    QTcpSocket *client;         // 客户端的socket
    QSqlDatabase db;            // 数据库句柄
    qint16 blocksize;
    Recv   Rec_msg;             // 接收的信息结构体

    QVector<QString> ques;      // 题干
    QVector<QString> answer1;   // 选项 1
    QVector<QString> answer2;   // 选项 2
    QVector<QString> answer3;   // 选项 3
    QVector<int> correct;       // 正确答案

    int timeID;                 // 定时器
    int num;
    int count;

};

inline QDataStream& operator << (QDataStream& out, Recv& send_msg)
{
    out << send_msg.cmd;
    out << send_msg.name;
    out << send_msg.passwd;
    out << send_msg.tele;
    out << send_msg.total;
    out << send_msg.level;

    out << send_msg.ques;
    out << send_msg.answer1;
    out << send_msg.answer2;
    out << send_msg.answer3;
    out << send_msg.correct;

    out << send_msg.EnemyName;
    return out;
}

inline QDataStream& operator >> (QDataStream& in, Recv& send_msg)
{
    in >> send_msg.cmd;
    in >> send_msg.name;
    in >> send_msg.passwd;
    in >> send_msg.tele;
    in >> send_msg.total;
    in >> send_msg.level;

    in >> send_msg.ques;
    in >> send_msg.answer1;
    in >> send_msg.answer2;
    in >> send_msg.answer3;
    in >> send_msg.correct;

    in >> send_msg.EnemyName;
    return in;
}

#endif // MYTHREAD_H
