#include <qapplication.h>
#include "Babel.hpp"

int						main(int ac, char **av) {
	QApplication		app(ac, av);
	Babel			babel;

	qRegisterMetaType<Sound::Encoded>();
	babel.run();
	window.show();
	return app.exec();
}
