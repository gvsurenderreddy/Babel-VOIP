#include <iostream>
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
