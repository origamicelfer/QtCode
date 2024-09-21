#include "widget.h"
#include "ui_widget.h"
const QString SERVER_IP = "192.168.31.124";
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("客户端");

    //实例化
    socket = new QTcpSocket(this);
    //连接服务器
    socket->connectToHost(SERVER_IP,9090);
    //  等待并确认连接是否出错.
     if (!socket->waitForConnected()) {
     QMessageBox::critical(nullptr, "连接服务器出错!", socket->errorString());
     exit(1);
     }
    //使用信号槽处理服务端返回的消息
    connect(socket,&QTcpSocket::readyRead,this,[=](){
        QString response = socket->readAll();
        if(!response.isEmpty())
        {
            QListWidgetItem* item = new QListWidgetItem("服务器："+response);
            //item->setTextAlignment(Qt::AlignRight);
            ui->listWidget->addItem(item);
        }
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    //1.读取line上面输入的内容
    QString data = ui->lineEdit->text();

    if(!data.isEmpty())
   {
        QListWidgetItem* item = new QListWidgetItem("客户端:"+data);
        item->setTextAlignment(Qt::AlignRight);
        ui->listWidget->addItem(item);
    }

    //2.写给服务器
    socket->write(data.toUtf8());

    //3.清空line edit
    ui->lineEdit->setText("");



}
