#include "registerdialog.h"
#include "ui_registerdialog.h"

#include <QPainter>
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    this->setFixedSize(660, 415);
    this->setStyleSheet("border:1px solid #92C8E8; margin: 0,0,0,0;");

    ui->setupUi(this);

    showIcon();
    ui->nicknameLayout->setAlignment(Qt::AlignRight);
    ui->pwdLayout->setAlignment(Qt::AlignRight);
    ui->confirmLayout->setAlignment(Qt::AlignRight);
    ui->registerLayout->setAlignment(Qt::AlignRight);
    ui->returnLayout->setAlignment(Qt::AlignRight);
    ui->bottomLayout->setAlignment(Qt::AlignCenter);

    // close the window when closeBtn is clicked
    connect(ui->closeBtn, &QPushButton::clicked, this, &RegisterDialog::close);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::showIcon()
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

void RegisterDialog::on_returnBtn_clicked()
{
    emit display(0);
}

void RegisterDialog::on_registerBtn_clicked()
{
    QString name = ui->nicknameLineEdit->text().trimmed();
    QString passwd = ui->passwdLineEdit->text().trimmed();
    QString confirmPasswd = ui->confirmLineEdit->text().trimmed();

    if (passwd != confirmPasswd) {
        QMessageBox::warning(this, "Warning", "两次输入密码不一致！");
        ui->confirmLineEdit->clear();
        return ;
    }

    QString registerMessage = "b," + name + "," + passwd;

    emit messageToServer(registerMessage);
    qDebug() << "Send register message to server";
}

void RegisterDialog::checkRegister(bool success)
{
    qDebug() << "Receive register feedback message from server";
    if (success) {
        emit registerSuccess(true);
        accept();
    } else {
        emit registerSuccess(false);
        QMessageBox::warning(this, "Warning", "用户名已被使用");
        ui->nicknameLineEdit->clear();
        ui->passwdLineEdit->clear();
        ui->confirmLineEdit->clear();
        return ;
    }
}
