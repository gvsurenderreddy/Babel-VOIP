#pragma once

#include <list>
#include "portaudio.h"
#include "ISoundDevice.hpp"
#include "Mutex.hpp"

class SoundOutputDevice : public ISoundDevice {

	// ctor - dtor
	public:
		SoundOutputDevice(void);
		~SoundOutputDevice(void);

	// private coplien form
	private:
		SoundOutputDevice(const SoundOutputDevice &) {}
		const SoundOutputDevice &operator=(const SoundOutputDevice &) { return *this; }

	// init
	private:
		void	initOutputDevice(void);

	// handle sound
	public:
		void	startStream(void);
		void	stopStream(void);

		ISoundDevice	&operator<<(const Sound::Decoded &soundBuffer);
		ISoundDevice	&operator>>(Sound::Decoded &soundBuffer);
		static int		callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

	// setters
	public:
		void	setOnSoundDeviceEventListener(ISoundDevice::OnSoundDeviceEvent *) {}

	// attributes
	private:
		std::list<Sound::Decoded *>			mBuffers;
		PaStreamParameters				mOutputParameters;
		PaStream					*mStream;
		Mutex						mMutex;
		bool						mIsRunning;

};
