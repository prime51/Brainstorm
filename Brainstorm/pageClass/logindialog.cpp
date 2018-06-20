#include "logindialog.h"
#include "ui_logindialog.h"

#include <QPainter>
#include <QPixmap>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    this->setFixedSize(660, 415);
    this->setStyleSheet("border:1px solid #92C8E8; margin: 0,0,0,0;");

    ui->setupUi(this);

    showIcon();
    ui->userLayout->setAlignment(Qt::AlignRight);
    ui->pwdLayout->setAlignment(Qt::AlignRight);
    ui->checkLayout->setAlignment(Qt::AlignJustify);
    ui->signInLayout->setAlignment(Qt::AlignRight);
    ui->restoreLayout->setAlignment(Qt::AlignRight);
    ui->bottomLayout->setAlignment(Qt::AlignCenter);

    ui->passwdLineEdit->setEchoMode(QLineEdit::Password);

    // close the window when closeBtn is clicked
    connect(ui->closeBtn, &QPushButton::clicked, this, &LoginDialog::close);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::showIcon()
{
    int width = 23, height = 23;
    QPixmap src(":/resources/images/icon");
    QPixmap pixmap(width, height);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, width, height);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, width, height, src);
    ui->iconLabel->setPixmap(pixmap);
    ui->iconLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
}

void LoginDialog::on_signInBtn_clicked()
{
    QString name = ui->userLineEdit->text().trimmed();
    QString passwd = ui->passwdLineEdit->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "用户名不能为空！");
        ui->userLineEdit->clear();
        ui->passwdLineEdit->clear();
        return ;
    } else if (passwd.isEmpty()) {
        QMessageBox::warning(this, "Warning", "密码不能为空！");
        ui->userLineEdit->clear();
        ui->passwdLineEdit->clear();
        return ;
    } else {
        emit messageToServer("a," + name + "," + passwd);
    }
}

void LoginDialog::on_registerBtn_clicked()
{
    emit display(1);
}

void LoginDialog::checkPasswd(bool success)
{
    if (success) {
        emit loginSuccess(true);
        accept();
    } else {
        emit loginSuccess(false);
        QMessageBox::warning(this, "Warning", "用户名或密码错误！");
        ui->userLineEdit->clear();
        ui->passwdLineEdit->clear();
        return ;
    }
}
