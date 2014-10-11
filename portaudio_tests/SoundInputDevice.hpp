#pragma once

#include "portaudio.h"

class SoundInputDevice {

	// input data struct
	private:
		struct InputData {
			int		frameIndex;
			int		maxFrameIndex;
			float	*recordedSamples;
		};

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
		float		*recordSound(int seconds);
		static int	recordCallback(const void *inputBuffer, void */*outputBuffer*/, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo */*timeInfo*/, PaStreamCallbackFlags /*statusFlags*/, void *userData);

	// attributes
	private:
		PaStreamParameters	mInputParameters;

		static const int	SAMPLE_RATE;
		static const int	NB_CHANNELS;
		static const int	FRAMES_PER_BUFFER;
		static const float	SAMPLE_SILENCE;

};
