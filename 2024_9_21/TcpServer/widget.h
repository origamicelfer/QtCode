#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void processConnection();
    QString process(QString request);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    QTcpServer* tcpserver;
    QTcpSocket* clientsocket;
};
#endif // WIDGET_H
