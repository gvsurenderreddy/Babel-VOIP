#include <qapplication.h>
#include "Babel.hpp"
#include <iostream>

int	main(int ac, char **av) {
	try {
		QApplication	app(ac, av);
		Babel			babel;

		babel.run();
		return app.exec();
	}
	catch (const std::exception &e) {
		std::cerr << "critical error caught" << std::endl;
		std::cerr << e.what() << std::endl;

		return -1;
	}
}
