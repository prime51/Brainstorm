#ifndef LOGINBUFPAGE_H
#define LOGINBUFPAGE_H

#include "logindialog.h"
#include "registerdialog.h"

#include <QObject>
#include <QString>
#include <QStackedWidget>

class loginBufPage : public QDialog
{
    Q_OBJECT

public:
    loginBufPage(QWidget *parent = 0);
    LoginDialog *loginDialog;
    RegisterDialog *registerDialog;
    QStackedWidget *stackWidget;

signals:
    void userID(QString id);

public slots:
    void loginSignal(bool success);
    void registerSignal(bool success);
    void exitSignal();
//    void sendUserID(QString id);

private:

};

#endif // LOGINBUFPAGE_H
