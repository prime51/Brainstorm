#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    ui->lineEdit_Port->setText("8765");
    ui->pushButton_Send->setEnabled(false);

    server = new QTcpServer();
    client_num = 0;

    //连接信号槽
    connect(server,&QTcpServer::newConnection,this,&Server::server_New_Connect);
}

Server::~Server()
{
    server->close();
    server->deleteLater();
    delete ui;
}

void Server::on_pushButton_Listen_clicked()
{
    if(ui->pushButton_Listen->text() == tr("侦听"))
    {
        //从输入框获取端口号
        int port = ui->lineEdit_Port->text().toInt();

        //监听指定的端口
        if(!server->listen(QHostAddress::Any, port))
        {
            //若出错，则输出错误信息
            qDebug()<<server->errorString();
            return;
        }
        //修改按键文字
        ui->pushButton_Listen->setText("取消侦听");
        qDebug()<< "Listen succeessfully!";
    }
    else
    {
        //如果正在连接
        if(client_num>0)
        {
            //关闭连接
            socket1->disconnectFromHost();
        }
        if(client_num==2)
        {
            //关闭连接
            socket2->disconnectFromHost();
        }
        //取消侦听
        server->close();
        //修改按键文字
        ui->pushButton_Listen->setText("侦听");
        //发送按键失能
        ui->pushButton_Send->setEnabled(false);
    }

}

void Server::on_pushButton_Send_clicked()
{
    qDebug() << "Send: " << ui->textEdit_Send->toPlainText();
    //获取文本框内容并以ASCII码形式发送
    if(client_num>0)
    {
        socket1->write(ui->textEdit_Send->toPlainText().toLocal8Bit());
        socket1->flush();
    }
    if(client_num == 2)
    {
        socket2->write(ui->textEdit_Send->toPlainText().toLatin1());
        socket2->flush();
    }
    ui->textEdit_Send->setText("");
}

void Server::server_New_Connect()
{
    //发送按键使能
    ui->pushButton_Send->setEnabled(true);
    if(client_num<2)client_num++;
    if(client_num==1)
    {
        //获取客户端连接
        socket1 = server->nextPendingConnection();
        //连接QTcpSocket的信号槽，以读取新数据
        QObject::connect(socket1, &QTcpSocket::readyRead, this, &Server::socket_Read_Data1);
        QObject::connect(socket1, &QTcpSocket::disconnected, this, &Server::socket_Disconnected);
        qDebug() << "A Client connect!";
    }
    else if(client_num==2)
    {
        //获取客户端连接
        socket2 = server->nextPendingConnection();
        //连接QTcpSocket的信号槽，以读取新数据
        QObject::connect(socket2, &QTcpSocket::readyRead, this, &Server::socket_Read_Data2);
        QObject::connect(socket2, &QTcpSocket::disconnected, this, &Server::socket_Disconnected);
        qDebug() << "B Client connect!";
    }
}

void Server::socket_Read_Data1()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket1->readAll();
    ui->textEdit_Recv->setText("");
    ui->textEdit_Recv->append(QString::fromLocal8Bit(buffer));
}

void Server::socket_Read_Data2()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket2->readAll();
    if(!buffer.isEmpty())
    {
        QString str = ui->textEdit_Recv->toPlainText();
        //str+=tr(buffer);
        str =tr(buffer);
        //刷新显示
        ui->textEdit_Recv->setText(str);
    }
}

void Server::socket_Disconnected()
{
    //发送按键失能
    ui->pushButton_Send->setEnabled(false);
    qDebug() << "Disconnected!";
}
