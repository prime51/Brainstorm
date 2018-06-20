#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

signals:
    void display(int n);        // used for change loginpage and registerpage
    void registerSuccess(bool success);
    void messageToServer(QString text);
                                // used to send message to server

public slots:
    void on_returnBtn_clicked();
    void on_registerBtn_clicked();
    void checkRegister(bool success);

private:
    Ui::RegisterDialog *ui;
    void showIcon();
};

#endif // REGISTERDIALOG_H
