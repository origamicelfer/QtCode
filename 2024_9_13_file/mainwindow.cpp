#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMenuBar>
#include<QMenu>
#include<QStatusBar>
#include<QAction>
#include<QTextEdit>
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //创建菜单栏
    QMenuBar* manubar = this->menuBar();

    //创建菜单
    QMenu* menu1 = new QMenu("文件");
    manubar->addMenu(menu1);
    //添加菜单选项
    QAction* action1 = new QAction("打开");
    QAction* action2 = new QAction("保存");
    menu1->addAction(action1);
    menu1->addAction(action2);

    //指定一个输入框
     edit = new QTextEdit();
    QFont font;
    font.setPixelSize(20);
    edit->setFont(font);
    this->setCentralWidget(edit);

    //连接Action的信号槽
    connect(action1,&QAction::triggered,this,&MainWindow::handle1);
     connect(action2,&QAction::triggered,this,&MainWindow::handle2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handle1()
{
    //1.读取打开文件的文件路径
    QString path = QFileDialog::getOpenFileName();

    //2.将读取到的文件路径显示到状态栏
    QStatusBar* statusbar = this->statusBar();
    statusbar->showMessage(path);
    //3.根据用户选择的路径，构造一个QFile对象,并打开文件
    QFile file(path);
    bool ret = file.open(QIODevice::ReadOnly);
    if(!ret)
    {
        //如果打开失败
        statusbar->showMessage(path + " 打开失败！");
    }
    //4.读取文件内容

    QString text = file.readAll();

    //5.关闭文件
    file.close();

    //6.将读取的内容显示到输入框中
    edit->setText(text);
}

void MainWindow::handle2()
{
    //1.读取打开文件的文件路径
    QString path = QFileDialog::getSaveFileName();

    //2.将读取到的文件路径显示到状态栏
    QStatusBar* statusbar = this->statusBar();
    statusbar->showMessage(path);
    //3.根据用户选择的路径，构造一个QFile对象,并打开文件
    QFile file(path);
    bool ret = file.open(QFile::WriteOnly);//
    if(!ret)
    {
        //如果打开失败
        statusbar->showMessage(path + " 打开失败！");
    }
    //4.输写文件内容

    const QString& text = edit->toMarkdown();

    //5.将输写的内容写进新文件中
    file.write(text.toUtf8());

    //6.关闭文件
    file.close();


}

