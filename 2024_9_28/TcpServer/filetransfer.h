#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>
#include"widget.h"
#include<QTcpServer>
#include<QTcpSocket>
#include<QFileDialog>
#include<QMessageBox>
#include<QThread>
#include<QDebug>
class FileTransfer : public QObject
{
    Q_OBJECT
public:
    explicit FileTransfer(QObject *parent = nullptr);

private slots:
    void delConnection();
    void loadFile(QTcpSocket *socket);
private:
    void delMsg(QTcpSocket* socket);
    void transferFileData(QTcpSocket* socket);
    void transferFileInfo(QTcpSocket* socket);

private:
    QTcpServer* m_tcpServer;
    qint64 m_sendFileSize;
    QString m_sendFilePath;
    QFile file;

signals:

};

#endif // FILETRANSFER_H
