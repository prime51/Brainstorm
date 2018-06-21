#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void display(int n);
    void loginSuccess(bool success);
    void exitConfirmed();
    void loginUserID(QString id);

    void messageToServer(QString text);

public slots:
    void on_signInBtn_clicked();
    void on_registerBtn_clicked();

    void checkPasswd(bool success);

private:
    Ui::LoginDialog *ui;
    void showIcon();
};

#endif // LOGINDIALOG_H
