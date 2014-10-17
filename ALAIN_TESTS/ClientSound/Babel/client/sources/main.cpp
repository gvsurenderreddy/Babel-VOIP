#include "SoundInputDevice.hpp"
#include "SoundOutputDevice.hpp"
#include "ReceiveSound.hpp"
#include <QtWidgets/QApplication>
#include <QThread>
#include <iostream>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	ReceiveSound receive;
	receive.show();
	std::cout << "APP.EXEC()" << std::endl;

	app.exec();

	/*
	SoundInputDevice input;
	SoundOutputDevice output;
	EncodeManager encodeManager;

	input.startStream();
	output.startStream();

	while (true) {
		Sound::Decoded *sound;

		input >> sound;
		if (sound) {
			Sound::Encoded encodedSound = encodeManager.encode(*sound);
			Sound::Decoded decodedSound = encodeManager.decode(encodedSound);
			output << &decodedSound;
		}
	}

	input.stopStream();
	output.stopStream();

	return 0;*/
}