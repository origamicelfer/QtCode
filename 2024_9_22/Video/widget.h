#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QHBoxLayout>//水平布局
#include<QVBoxLayout>//垂直布局
#include<QMediaPlayer>//播放媒体
#include<QVideoWidget>//显示视频
#include<QPushButton>//按钮
#include<QStyle>//设置图标
#include<QFileDialog>//选择文件
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void  chooseVideo();
    void playVideo();

private:
    Ui::Widget *ui;
    QMediaPlayer* mediaplayer;
    QVideoWidget* videowidget;
    QVBoxLayout *vbox;//垂直布局
    QPushButton* chooseBtn,*playBtn;//选择和开播放按钮

};
#endif // WIDGET_H
