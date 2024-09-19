#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    Thread t1;
    Thread t2;
    t1.start();
    t2.start();

    //因为是并行执行线程，所以主线程这里要等等两个线程执行结束
    t1.wait();
    t2.wait();

    //打印结果
    qDebug()<<"num:"<<Thread::num<<endl;
}

Widget::~Widget()
{
    delete ui;
}

