#pragma once

#include "Sound.hpp"

class ISoundDevice {

	// virtual destructor
	public:
		virtual ~ISoundDevice(void) {}

	// virtual methods
	public:
		virtual void	startStream(void) = 0;
		virtual void	stopStream(void) = 0;

		virtual ISoundDevice	&operator<<(const Sound::Decoded &soundBuffer) = 0;
		virtual ISoundDevice	&operator>>(Sound::Decoded &soundBuffer) = 0;

};
