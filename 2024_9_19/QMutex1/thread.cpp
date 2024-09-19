#include "thread.h"
#include "widget.h"
//定义变量
int Thread::num = 0;
QMutex Thread::mutex;
Thread::Thread()
{

}

void Thread::run()
{

    for(int i = 0;i<24;i++)
    {
        QMutexLocker mutex_locker(&mutex);//自动释放锁
            num++;
//        mutex.lock();
//        num++;
//        mutex.unlock();
    }
}
