#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //连接信号槽
    connect(&mythread,&MyThread::notify,this,&Widget::handle);//发出信号者和处理信号者
    mythread.start();//开启线程
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handle()
{
    int value = ui->lcdNumber->value();
    if(value>=0)
    {
        value--;
        ui->lcdNumber->display(value);
    }

}

