#pragma once

#include <list>
#include "portaudio.h"
#include "ISoundDevice.hpp"

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

		ISoundDevice	&operator<<(SoundBuffer *soundBuffer);
		ISoundDevice	&operator>>(SoundBuffer *&soundBuffer);
		static int		callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

	// attributes
	private:
		std::list<ISoundDevice::SoundBuffer *> mBuffers;
		PaStreamParameters	mOutputParameters;
		PaStream *mStream;

		static const int	SAMPLE_RATE;
		static const int	NB_CHANNELS;
		static const int	FRAMES_PER_BUFFER;

};
