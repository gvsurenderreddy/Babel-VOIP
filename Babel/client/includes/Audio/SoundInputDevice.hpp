#pragma once

#include <list>
#include "portaudio.h"
#include "ISoundDevice.hpp"
#include "Mutex.hpp"

class SoundInputDevice : public ISoundDevice {

	// ctor - dtor
	public:
		SoundInputDevice(void);
		~SoundInputDevice(void);

	// private coplien form
	private:
		SoundInputDevice(const SoundInputDevice &) {}
		const SoundInputDevice &operator=(const SoundInputDevice &) { return *this; }

	// init
	private:
		void	initInputDevice(void);

	// handle sound
	public:
		void	startStream(void);
		void	stopStream(void);

		ISoundDevice	&operator<<(const Sound::Decoded &soundBuffer);
		ISoundDevice	&operator>>(Sound::Decoded &soundBuffer);
		static int		callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

	// attributes
	private:
		std::list<Sound::Decoded *>	mBuffers;
		PaStreamParameters			mInputParameters;
		PaStream					*mStream;
		Mutex						mMutex;
		bool						mIsRunning;

};
