#include "mythread.h"

MyThread::MyThread()
{

}

void MyThread::run()
{
    for(int i = 0;i<10;i++)
    {
        sleep(1);
       emit notify();//通知主线程
    }
}
