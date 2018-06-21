#ifndef MAINPAGE_H
#define MAINPAGE_H

#include "hoversensitivelabel.h"
#include "pageClass/loginbufpage.h"
#include "pageClass/gamepage.h"

#include <QWidget>
#include <QTcpSocket>
#include <QString>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    loginBufPage *loginPage;
    GamePage *gamePage;

    QTcpSocket *socket;

    explicit MainPage(QWidget *parent = 0);
    ~MainPage();

private:
    Ui::MainPage *ui;
    HoverSensitiveLabel *hoverLabel;
    QString UserID;

    void showAvatar(QString picPath);
    void showIcon();

    void createLoginPage();

signals:
    void sendLoginMessage(bool success);
    void sendRegisterMessage(bool success);
    void sendSingleGame(QString queMessage);
    void sendMatchGame();

public slots:
    void setUserID(QString id);         // get signal from login page and set userID in mainpage
    void on_singleTrainBtn_clicked();   // start single training game
    void on_exitLoginBtn_clicked();     // exit login, return to login page

    void sendMessage(QString text);     // use socket to send message to server
    void handleMessage();               // handle messages from server
};

#endif // MAINPAGE_H
