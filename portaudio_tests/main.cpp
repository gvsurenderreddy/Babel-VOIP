#include <iostream>
#include "SoundInputDevice.hpp"
#include "SoundOutputDevice.hpp"

int main(void) {
	SoundInputDevice input;
	SoundOutputDevice output;
	float *sound;

	std::cout << "recording..." << std::endl;
	sound = input.recordSound(5);
	std::cout << "playing..." << std::endl;
	output.playSound(sound, 5);

	return 0;
}
