#include <qapplication.h>
#include "Babel.hpp"

int						main(int ac, char **av) {
	QApplication		app(ac, av);
	BabelMainWindow		gui;

	gui.show();
	/*Babel				babel;

	qRegisterMetaType<Sound::Encoded>();
	babel.run();*/
	return app.exec();
}
