#include <qapplication.h>
#include "Babel.hpp"

int main(int ac, char **av) {
	QApplication	app(ac, av);
	Babel			babel;

	babel.run();
	return app.exec();
}
