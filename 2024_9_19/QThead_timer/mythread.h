#ifndef MYTHREAD_H
#define MYTHREAD_H
#include<QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
    void run() override;
signals:
    void notify();//通知主线程
};

#endif // MYTHREAD_H
