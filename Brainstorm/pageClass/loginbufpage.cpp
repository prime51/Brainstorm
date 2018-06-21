#include "loginbufpage.h"

#include <QDebug>
#include <QVBoxLayout>

loginBufPage::loginBufPage(QWidget *parent)
    : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);             // delete the object right after it is closed
//    setWindowFlags(Qt::Widget);
//    this->setFixedSize(660, 415);

    loginDialog = new LoginDialog(this);
    registerDialog = new RegisterDialog(this);

    stackWidget = new QStackedWidget(this);
    qDebug() << "Hello at loginbufoage.cpp @ line 12";
    stackWidget->addWidget(loginDialog);
    stackWidget->addWidget(registerDialog);
    qDebug() << "Hello at loginbufoage.cpp @ line 15";
    connect(loginDialog, &LoginDialog::display, stackWidget, &QStackedWidget::setCurrentIndex);
    connect(registerDialog, &RegisterDialog::display, stackWidget, &QStackedWidget::setCurrentIndex);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackWidget);
    mainLayout->setMargin(0);
    setLayout(mainLayout);

    connect(loginDialog, &LoginDialog::loginSuccess, this, &loginBufPage::loginSignal);
    connect(registerDialog, &RegisterDialog::registerSuccess, this, &loginBufPage::registerSignal);
    connect(loginDialog, &LoginDialog::exitConfirmed, this, &loginBufPage::exitSignal);
    connect(loginDialog, &LoginDialog::loginUserID, this, &loginBufPage::userID);
}

void loginBufPage::loginSignal(bool success)
{
    if (success == true) {
        qDebug() << "loginbufpage receives successful login signal";
        accept();
        close();
    } else {
        qDebug() << "login failed";
    }
}

void loginBufPage::registerSignal(bool success)
{
    if (success == true) {
        qDebug() << "loginbufpage receives successful register signal";
        accept();
        close();
    } else {
        qDebug() << "register failed";
    }
}

void loginBufPage::exitSignal()
{
    this->close();
}
