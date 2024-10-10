#include "widget.h"
#include "ui_widget.h"
const QString SERVER_IP = "127.0.0.1";
const qint16 SERVER_PORT = 9090;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("客户端");
    isDownloading = false;
   //1.实例化
    m_tcpSocket = new QTcpSocket(this);

    //2.连接服务器
    m_tcpSocket->connectToHost(SERVER_IP,SERVER_PORT);
    if(!m_tcpSocket->waitForConnected())
    {
        QMessageBox::critical(nullptr,"连接主机失败！",m_tcpSocket->errorString());
        exit(1);
    }

    //3.用信号槽处理主机发来的消息
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,[=](){
        delMsg();
    });

}

Widget::~Widget()
{
    delete ui;
}
void Widget::delMsg()
{
    if(isDownloading)
        receiveData();
    else
        receiveInfo();
}

void Widget::receiveInfo()
{

    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_5_12);
    int msgType;
    in>>msgType>>m_sendFileSize;
    if(msgType==FileInfo)
    {
        QString info = QString("客户端发来info[msgType:%1;sendFileSize:%2]").arg(msgType).arg(m_sendFileSize);
        QListWidgetItem* item = new QListWidgetItem(info);
        ui->listWidget->addItem(item);
    }
}

void Widget::receiveData()
{
    if(!file.isOpen())
    {
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug()<<"文件打开失败!"<<file.errorString();
        }
    }


   qint64 readBytes = m_tcpSocket->bytesAvailable();
    // 如果接收的数据大小小于要接收的文件大小，那么继续写入文件
    if(bytesReceived<m_sendFileSize) {
        // 返回等待读取的传入字节数
        QByteArray data = m_tcpSocket->read(readBytes);
        bytesReceived+=readBytes;
        file.write(data);
        QString debug = QString("已写入[bytesReceived:%1;m_sendFileSize:%2]").arg(bytesReceived).arg(m_sendFileSize);
        qDebug()<<debug;
        if(bytesReceived>=m_sendFileSize)
        {
            qDebug()<<"全部接收,文件关闭";
            isDownloading = false;
            bytesReceived = 0;
            file.close();
        }
    }


}


void Widget::on_pushButton_clicked()
{

    m_downloadPath = QFileDialog::getSaveFileName(nullptr,"保存文件","D:/A/QtProject/2024_9_28","Textfiles(*.txt);;Images(*.jpg *.png);;音乐(*.mp3);;视频(*.mp4)");
    file.setFileName(m_downloadPath);
    qDebug()<<"file setFileName:"<<file.fileName();
    isDownloading = true;
    //发送Data消息让服务端发送Data
    QByteArray byteArray;
    int msgType = FileData;
    QDataStream out(&byteArray,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out<<(int)msgType;
    m_tcpSocket->write(byteArray);
    if (!m_tcpSocket->waitForBytesWritten(3000)) {
        // 处理超时
        qDebug()<<"发送Data消息让服务端发送Data失败!";
    }
    else
    {
        qDebug()<<"发送Data消息让服务端发送Data";
    }

}
