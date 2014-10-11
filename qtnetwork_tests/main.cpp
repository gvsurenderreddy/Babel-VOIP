#include "qtnetwork_tests.h"
#include <QtWidgets/QApplication>
#include "WindowsTcpClient.hpp"
#include "WindowsTcpServer.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qtnetwork_tests w;
	w.show();
	return a.exec();
}
