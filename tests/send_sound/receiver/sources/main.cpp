#include "ReceiveSound.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	ReceiveSound receive;

	app.exec();

}