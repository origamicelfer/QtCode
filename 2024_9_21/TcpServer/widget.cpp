#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器");

    //实例化
    tcpserver = new QTcpServer(this);
    //通过信号槽，处理与客户端建立起来的连接
    connect(tcpserver,&QTcpServer::newConnection,this,&Widget::processConnection);

    //listen客户端
    bool ret = tcpserver->listen(QHostAddress::Any,9090);
    if(!ret)
    {
        QMessageBox::critical(nullptr,"服务器启动失败!",tcpserver->errorString());
        return;
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::processConnection()
{
    //1.返回客户端连接的socket
     clientsocket = tcpserver->nextPendingConnection();
    QString log = "["+clientsocket->peerAddress().toString()+":"+QString::number(clientsocket->peerPort())
            +"]客户端上线！";
    ui->listWidget->addItem(log);
    //2.通过信号槽，处理收到的请求
//    connect(clientsocket,&QTcpSocket::readyRead,this,[=](){
//        QString request = clientsocket->readAll();
//        QString response = process(request);
//        //将response写回客户端
//        if(!response.isEmpty())
//        {
//            clientsocket->write(response.toUtf8());
//            QString log = "["+clientsocket->peerAddress().toString()+":"+QString::number(clientsocket->peerPort())
//                    +"]:"+"req:"+request+"  "+"resp:"+response;
//            ui->listWidget->addItem(log);
//        }
//    });
    //2.将来自客户端的消息addItem
        connect(clientsocket,&QTcpSocket::readyRead,this,[=](){
            QString request = clientsocket->readAll();
            if(!request.isEmpty())
           {
                QListWidgetItem* item = new QListWidgetItem("客户端:"+request);

                ui->listWidget->addItem(item);
            }

        });
    //3.通过信号槽，处理客户端断开情况
    connect(clientsocket,&QTcpSocket::disconnected,this,[=](){
        QString log = "["+clientsocket->peerAddress().toString()+":"+QString::number(clientsocket->peerPort())
                +"]客户端下线";
        ui->listWidget->addItem(log);
        clientsocket->deleteLater();
    });

}

QString Widget::process(QString request)
{
    return request;


}


void Widget::on_pushButton_clicked()
{
    QString data = ui->lineEdit->text();


    if(!data.isEmpty())
   {
        QListWidgetItem* item = new QListWidgetItem("服务器:"+data);
        item->setTextAlignment(Qt::AlignRight);
        ui->listWidget->addItem(item);
    }
    //清空line edit
    ui->lineEdit->setText("");

    clientsocket->write(data.toUtf8());


}
