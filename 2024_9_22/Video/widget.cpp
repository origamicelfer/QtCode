#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //实例化
    mediaplayer = new QMediaPlayer(this);
    videowidget = new QVideoWidget(this);

    videowidget->setMinimumSize(600,600);//设置播放窗口大小

    //设置垂直布局
    vbox = new QVBoxLayout(this);
    this->setLayout(vbox);

    //设置按钮
    chooseBtn = new QPushButton("选择视频",this);
    playBtn = new QPushButton(this);
    playBtn->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));

    //创建水平布局并把按钮放入水平布局中
    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(chooseBtn);
    hbox->addWidget(playBtn);
    //将播放窗口放入垂直布局,水平布局放入垂直布局中
    vbox->addWidget(videowidget);
    vbox->addLayout(hbox);

    //通过信号槽处理clicked选择视频信号
    connect(chooseBtn,&QPushButton::clicked,this,&Widget::chooseVideo);
    //通过信号槽处理播放按钮
    connect(playBtn,&QPushButton::clicked,this,&Widget::playVideo);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::chooseVideo()
{
    //获取打开的视频文件的path
    QString path = QFileDialog::getSaveFileName(this,"选择视频","D:/PR/pr素材/视频","MP4(*.mp4)");

    //设置媒体
    mediaplayer->setMedia(QUrl(path));

    //输出视频画面
    mediaplayer->setVideoOutput(videowidget);

    //播放
    mediaplayer->play();
}

void Widget::playVideo()
{
    mediaplayer->play();
}

