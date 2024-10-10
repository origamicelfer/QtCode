#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QFileDialog>
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
    void delMsg(QTcpSocket* socket);


private slots:
    void delConnection();
    void loadFile(QTcpSocket *socket);
private:
    void transferFileData(QTcpSocket* socket);
    void transferFileInfo(QTcpSocket* socket);

private:
    Ui::Widget *ui;
    QTcpServer* m_tcpServer;
private:

    qint64 m_sendFileSize;
    QString m_sendFilePath;
    QFile file;
};
#endif // WIDGET_H
