#include "filetransfer.h"

FileTransfer::FileTransfer(QObject *parent) : QObject(parent)
{

}
void FileTransfer::delMsg(QTcpSocket *socket)
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);
    int typeMsg;
    in>>typeMsg;
    if(typeMsg == MsgType::FileData) {
        // 发送文件数据
        qDebug()<<"主机收到Data消息,准备发送Data";
        transferFileData(socket);
    }
    else {
        qDebug()<<"typeMsg!=FileData,不能发送";
    }
}
void FileTransfer::delConnection()
{
    //1.返回客户端连接的socket
    QTcpSocket* socket = m_tcpServer->nextPendingConnection();
    QString log = "["+socket->peerAddress().toString()+":"+QString::number(socket->peerPort())
            +"]客户端上线！";
    Widget::getUi()->listWidget->addItem(log);

    //2.readyread
    connect(socket,&QTcpSocket::readyRead,this,[=](){
        qDebug()<<"主机readyRead";
        delMsg(socket);
    });

    //3.sendFile
    connect(Widget::getUi()->pushButton,&QPushButton::clicked,this,[=](){
        loadFile(socket);
    });

    //4.检查disconnected
    connect(socket,&QTcpSocket::disconnected,this,[=](){
        QString log = "["+socket->peerAddress().toString()+":"+QString::number(socket->peerPort())
                +"]客户端下线！";
        Widget::getUi()->listWidget->addItem(log);
        socket->deleteLater();
    });

}

void FileTransfer::loadFile(QTcpSocket *socket)
{
    m_sendFilePath = QFileDialog::getOpenFileName(nullptr,"打开文件","D:/A/QtProject/2024_9_28");
    file.setFileName(m_sendFilePath);
    m_sendFileSize = file.size();

    //发送Info
    transferFileInfo(socket);

}

void FileTransfer::transferFileInfo(QTcpSocket *socket)
{
    QByteArray sendInfo;
    QDataStream out(&sendInfo,QIODevice::WriteOnly);
    int typeMsg = FileInfo;
    out<<(int)typeMsg<<(qint64)m_sendFileSize;

    socket->write(sendInfo);
}
void FileTransfer::transferFileData(QTcpSocket *socket)
{
    qDebug()<<"主机开始发送Data";
    //打开文件
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"打开文件失败！"<<file.errorString();
    }
    qint64 payloadSize = 1024*64; //每一帧发送1024*64个字节，控制每次读取文件的大小，从而传输速度
    qint64 bytesWritten=0;//已经发送的字节数

    while(bytesWritten != m_sendFileSize) {

        if(bytesWritten<m_sendFileSize){

            QByteArray DataInfoBlock = file.read(qMin(m_sendFileSize,payloadSize));

            qint64 WriteBolockSize = socket->write(DataInfoBlock, DataInfoBlock.size());

            //QThread::msleep(1); //添加延时，防止服务端发送文件帧过快，否则发送过快，客户端接收不过来，导致丢包
            QThread::usleep(3); //添加延时，防止服务端发送文件帧过快，否则发送过快，客户端接收不过来，导致丢包
            //等待发送完成，才能继续下次发送，
            if(!socket->waitForBytesWritten(3*1000)) {

                return;
            }

            bytesWritten += WriteBolockSize;
            QString debug = QString("单次发送[bytesWritten:%1;m_sendFileSize:%2]").arg(bytesWritten).arg(m_sendFileSize);
            qDebug()<<debug;

        }

    }

    //发送完成,关闭文件
    qDebug()<<"发送完成！关闭文件";
    file.close();

}
