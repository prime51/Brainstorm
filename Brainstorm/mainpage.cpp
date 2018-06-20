#include "mainpage.h"
#include "ui_mainpage.h"
#include "pageClass/loginbufpage.h"

#include <QPixmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QHostAddress>
#include <QNetworkInterface>

const QString IP_Addr = "172.19.240.206";

//QHostAddress getIP_Addr()
//{
//    foreach (const QHostAddress &hostAddress, QNetworkInterface::allAddresses()) {
//        if (hostAddress != QHostAddress::LocalHost && hostAddress.toIPv4Address())
//            return hostAddress;
//    }
//    return QHostAddress::LocalHost;
//}

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(500, 700);
    this->setStyleSheet("border:1px solid #92C8E8; margin: 0,0,0,0;");

    ui->setupUi(this);

    // add hoverable label in widget, representing avatar
    hoverLabel = new HoverSensitiveLabel(ui->bottomCenterWidget);
    ui->avatarHLayout->setAlignment(Qt::AlignCenter);
    ui->avatarHLayout->addWidget(hoverLabel);

    showIcon();
    showAvatar(":/resources/images/background");
    ui->singleTrainHLayout->setAlignment(Qt::AlignJustify);
    ui->singleTrainHLayout->setMargin(20);
    ui->matchHLayout->setAlignment(Qt::AlignJustify);
    ui->matchHLayout->setMargin(20);
    ui->exitLoginHLayout->setAlignment(Qt::AlignJustify);
    ui->exitLoginHLayout->setMargin(20);
    ui->bottomLayout->setAlignment(Qt::AlignCenter);

    createLoginPage();
    connect(ui->closeBtn, &QPushButton::clicked, this, &MainPage::close);

    QString IP_Addr = getIP_Addr().toString();
    qDebug() << IP_Addr;
    socket = new QTcpSocket();
//    while (true) {
        socket->connectToHost(IP_Addr, 6666);
        if(!socket->waitForConnected(3000)) {
            QMessageBox::warning(this, "Warning", "网络未连接！请检查网络是否接入局域网。", QMessageBox::Ok);
            qDebug() << "Connection failed!";
            loginPage->close();
            close();
        } else {
            qDebug() << "Connection succeed";
        }
//    }

    // connect receive-message signal to handleMessage function
    connect(socket, &QTcpSocket::readyRead, this, &MainPage::handleMessage);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::createLoginPage()
{
    loginPage = new loginBufPage(this);
    // send user ID from loginpage to mainpage
    connect(loginPage, &loginBufPage::userID, this, &MainPage::setUserID);
    // connect mainpage and loginpage(logindialog + registerdialog) to send message to server
    connect(loginPage->loginDialog, &LoginDialog::messageToServer,
            this, &MainPage::sendMessage);
    connect(loginPage->registerDialog, &RegisterDialog::messageToServer,
            this, &MainPage::sendMessage);
    // connect login response message to loginpage
    connect(this, &MainPage::sendLoginMessage, loginPage->loginDialog, &LoginDialog::checkPasswd);
    // connect register response message to registerpage
    connect(this, &MainPage::sendRegisterMessage, loginPage->registerDialog, &RegisterDialog::checkRegister);
}

void MainPage::showIcon()
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

void MainPage::showAvatar(QString picPath)
{
    hoverLabel->setFixedSize(80, 80);

    int less = hoverLabel->width();

    QString roundBorder;
    roundBorder.sprintf("border-radius: %d px;", less / 2);
    hoverLabel->setStyleSheet(roundBorder);

    QPixmap pixmapa(picPath);
    QPixmap pixmap(less,less);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, less, less);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, less, less, pixmapa);
    hoverLabel->setPixmap(pixmap);
    hoverLabel->setAlignment(Qt::AlignHCenter);
}

void MainPage::setUserID(QString id)
{
    UserID = id;
}

void MainPage::on_singleTrainBtn_clicked()
{
    gamePage = new GamePage;

    // connect mainpage and gamepage to send message to server
    connect(gamePage, &GamePage::messageToServer, this, &MainPage::sendMessage);
    // connect mainpage and gamepage to send message to server
    connect(this, &MainPage::sendSingleGame, gamePage, &GamePage::prepareQuestions);

    sendMessage("d");
    // show main page after game ends
    connect(gamePage, &GamePage::gameEnds, this, &MainPage::show);
    this->hide();
    gamePage->show();
}

void MainPage::on_exitLoginBtn_clicked()
{
    this->close();
    createLoginPage();
    if (loginPage->exec() == QDialog::Accepted) {
        this->show();
    }
}

void MainPage::sendMessage(QString text)
{
    socket->write(text.toLocal8Bit());
    socket->flush();
}

void MainPage::handleMessage()
{
    QString message = QString::fromUtf8(socket->readAll());
    QString mode = message.section(",", 0, 0);

    if (mode == "a") {
        QString loginSuccess = message.section(",", 1, 1);
        if (loginSuccess == "s")
            emit sendLoginMessage(true);
        else if (loginSuccess == "f")
            emit sendLoginMessage(false);
        else
            qDebug() << "Invalid login message";
    }
    else if (mode == "b") {
        QString registerSuccess = message.section(",", 1, 1);
        if (registerSuccess == "s")
            emit sendRegisterMessage(true);
        else
            emit sendRegisterMessage(false);
    }
    else if (mode == "d") {
        QString queMessage = message.section(",", 1, 1);
        emit sendSingleGame(queMessage);
    }
}
