#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QFileDialog>

#include<QMessageBox>
#include<QThread>
#include<QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
enum MsgType{
    FileInfo,   //文件信息，如文件名，文件大小等信息
    FileData,   //文件数据，即文件内容
};
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

private:
    void delMsg();
    void receiveInfo();
    void receiveData();

private:
    Ui::Widget *ui;
    QTcpSocket* m_tcpSocket;
    qint64 m_sendFileSize;
    qint64 bytesReceived;
    QString m_downloadPath;//下载路径
    QFile file;
    bool isDownloading; //是否正在下载标识
};
#endif // WIDGET_H
