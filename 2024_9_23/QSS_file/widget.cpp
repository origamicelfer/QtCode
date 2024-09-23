#include "widget.h"
#include "ui_widget.h"
#include<QFile>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString style = Widget::loadQss();
    this->setStyleSheet(style);
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::loadQss()
{
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);

    QString style = file.readAll();

    return style;
}

