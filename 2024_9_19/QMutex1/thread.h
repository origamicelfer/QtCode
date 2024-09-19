#ifndef THREAD_H
#define THREAD_H
#include<QThread>
#include<QMutex>
#include<QMutexLocker>
class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
    static int num ;
    static QMutex mutex;//对所有线程进行上锁的互斥锁必须是同一个对象才行,所以设置为static

    void run() override;
};

#endif // THREAD_H
