#pragma once

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "ReceiveSound.hpp"

class MyThread : public QThread
{
	Q_OBJECT
public:
	MyThread(ReceiveSound *parent);

public:
	void run();

	ReceiveSound *mtoto;

};
 
#endif // MYTHREAD_H