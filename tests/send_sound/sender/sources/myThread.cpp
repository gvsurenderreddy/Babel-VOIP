#include "myThread.hpp"
#include <iostream>
#include <QThread>
#include <QDebug>
#include "ReceiveSound.hpp"

MyThread::MyThread(ReceiveSound *r) : QThread(), mtoto(r)
{
}

void MyThread::run()
{
	mtoto->onThreadStart();
}