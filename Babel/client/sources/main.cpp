#include "SoundInputDevice.hpp"
#include "SoundOutputDevice.hpp"
#include "EncodeManager.hpp"

int main(void) {
	SoundInputDevice input;
	SoundOutputDevice output;
	EncodeManager encodeManager;

	input.startStream();
	output.startStream();

	while (true) {
		Sound::Decoded sound;

		input >> sound;
		if (sound.buffer)
			output << encodeManager.decode(encodeManager.encode(sound));
	}

	input.stopStream();
	output.stopStream();

	return 0;
}
