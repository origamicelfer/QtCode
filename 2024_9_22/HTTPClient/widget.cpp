#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //实例化对象
    manager = new QNetworkAccessManager(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    //1.构造QUrl对象
    QUrl url(ui->lineEdit->text());

    //2.构造request对象
    QNetworkRequest request(url);

    //3.发起get请求
    QNetworkReply* reply = manager->get(request);

    //4.通过信号槽来处理响应
    connect(reply,&QNetworkReply::finished,this,[=](){
        if(reply->error()==QNetworkReply::NoError)
        {
            //说明请求成功
            QString html(reply->readAll());
            ui->plainTextEdit->setPlainText(html);

        }
        else
        {
            ui->plainTextEdit->setPlainText(reply->errorString());
        }
        reply->deleteLater();
    });

}
