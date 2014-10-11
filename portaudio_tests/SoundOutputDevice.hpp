#pragma once

#include "portaudio.h"

class SoundOutputDevice {

	// input data struct
	private:
		struct OutputData {
			int		frameIndex;
			int		maxFrameIndex;
			float	*recordedSamples;
		};

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
		void		playSound(float *sound, int seconds);
		static int	playCallback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

	// attributes
	private:
		PaStreamParameters	mOutputParameters;

		static const int	SAMPLE_RATE;
		static const int	NB_CHANNELS;
		static const int	FRAMES_PER_BUFFER;

};
