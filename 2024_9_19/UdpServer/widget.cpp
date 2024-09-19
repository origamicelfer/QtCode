#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("服务器");
    //创建socket对象
    socket = new QUdpSocket(this);

    //连接信号槽
    connect(socket,&QUdpSocket::readyRead,this,&Widget::processRequest);

    //绑定端口号
    bool ret = socket->bind(QHostAddress::Any,9090);
    if(!ret)
     {
        QMessageBox::critical(nullptr,"服务器启动出错",socket->errorString());
        return;
    }

}

Widget::~Widget()
{
    delete ui;
}

void Widget::processRequest()
{
    //1.读取请求
    const QNetworkDatagram& requestDatagram = socket->receiveDatagram();
    QString request = requestDatagram.data();
    //2.根据请求计算响应
    const QString& response = process(request);
    //3.把响应写回客户端
    QNetworkDatagram responseDatagram(response.toUtf8(),requestDatagram.senderAddress(),requestDatagram.senderPort());
    socket->writeDatagram(responseDatagram);
    //4.将交互信息显示到listWidget上
    QString log = "[" + requestDatagram.senderAddress().toString() + ":" +
    QString::number(requestDatagram.senderPort())
     + "] req: " + request + ", resp: " + response;
     ui->listWidget->addItem(log);

}

QString Widget::process(QString request)
{
    return request;
}


