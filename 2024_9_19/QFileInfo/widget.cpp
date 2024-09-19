#include "widget.h"
#include "ui_widget.h"
#include<QFileInfo>
#include<QFileDialog>
#include<QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString path = QFileDialog::getOpenFileName(this);
    QFileInfo info(path);
    if(info.exists())
    {
        qDebug()<<"file name:"<<info.fileName();
        qDebug()<<"file path:"<<info.absoluteFilePath();
        qDebug()<<"file size:"<<info.size();
    }
}

Widget::~Widget()
{
    delete ui;
}

