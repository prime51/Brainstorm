#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QPushButton"
#include <QDialog>

class Dialog;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->passwordLine->setEchoMode(QLineEdit::Password);//当输入密码时，显示为*******
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_forget_psd_clicked()
{
    close();  //当用户忘记密码时候，单击forget passward按键，直接退出程序
}

void MainWindow::on_login_in_clicked()
{
    if(this->ui->nameLine->text().trimmed() == tr("Manuel") &&
       this->ui->passwordLine->text().trimmed()== tr("123456789"))  //去除lineEdit内的用户名和密码进行校验
    {
        //登陆成功后显示对话框
        Dialog *dialogLogin=new Dialog;
        dialogLogin->dialogUse();
    }
    else
    {
        //用户输入存在错误
        QMessageBox::warning(this,tr("waring"),tr("your passward is wrong"),QMessageBox::Yes);
        ui->nameLine->clear();  //清空姓名nameLine
        ui->passwordLine->clear();  //清空密码passwardLine
        ui->nameLine->setFocus();  //将鼠标重新定位到nameLine
    }
}

Dialog::Dialog(QDialog *parent)
    :QDialog(parent)
{
    dialog=new QDialog();
    dialog->setWindowTitle(tr("Manuel"));
}

void Dialog::dialogUse()
{
    dialog->show();
}

void Dialog::findClick()
{
}

void Dialog::enableFindButton()
{
}

Dialog::~Dialog()  //Dialog类的析构函数里面不知道写什么，就没写，哈哈......
{
}
