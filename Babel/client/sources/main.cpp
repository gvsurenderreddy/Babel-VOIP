#include <qapplication.h>
#include "Babel.hpp"
#include <QMetaType>
#include "Sound.hpp"

int						main(int ac, char **av) {
	QApplication		app(ac, av);
	BabelMainWindow		window;
	/*Babel			babel;

	qRegisterMetaType<Sound::Encoded>();
	babel.run();*/
	window.show();
	return app.exec();
}
