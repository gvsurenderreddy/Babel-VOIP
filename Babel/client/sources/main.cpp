#include <iostream>

/* PORTAUDIO TEST */
/*
#include "SoundInputDevice.hpp"
#include "SoundOutputDevice.hpp"

int main(void) {
	SoundInputDevice input;
	SoundOutputDevice output;

	input.startStream();
	output.startStream();

	while (true) {
		ISoundDevice::SoundBuffer *buffer;

		input >> buffer;
		if (buffer)
			output << buffer;
	}

	input.stopStream();
	output.stopStream();

	return 0;
}
*/

/* QT NETWORK TEST */
#include <qapplication.h>
#include "SimpleWindow.hpp"

int	main(int ac, char **av) {
	QApplication app(ac, av);

	SimpleWindow simpleWindow;
	simpleWindow.show();

	return app.exec();
}
