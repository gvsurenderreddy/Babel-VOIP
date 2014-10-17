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

	return 0;
}
