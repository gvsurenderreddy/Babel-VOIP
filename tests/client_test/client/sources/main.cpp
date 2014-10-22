#include <qapplication.h>
#include "Sender.hpp"
#include "Receiver.hpp"

int main(int ac, char **av) {
	/* SENDER */
	/*
	QApplication app(ac, av);
	Sender sender;

	sender.start();
	return app.exec();
	*/


	QApplication app(ac, av);
	Receiver receiver;

	receiver.start();
	return app.exec();


	return 0;
}
