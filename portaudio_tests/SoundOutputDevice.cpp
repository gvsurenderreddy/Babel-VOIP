#include "SoundOutputDevice.hpp"
#include "SoundDeviceException.hpp"

const int SoundOutputDevice::SAMPLE_RATE = 44100;
const int SoundOutputDevice::NB_CHANNELS = 2;
const int SoundOutputDevice::FRAMES_PER_BUFFER = 512;

SoundOutputDevice::SoundOutputDevice(void) {
	if (Pa_Initialize() != paNoError)
		throw new SoundDeviceException("fail Pa_Initialize");

	initOutputDevice();
}

SoundOutputDevice::~SoundOutputDevice(void) {
	Pa_Terminate();
}

void	SoundOutputDevice::initOutputDevice(void) {
	mOutputParameters.device = Pa_GetDefaultOutputDevice();
	if (mOutputParameters.device == paNoDevice)
		throw new SoundDeviceException("fail Pa_GetDefaultOutputDevice");

	mOutputParameters.channelCount = SoundOutputDevice::NB_CHANNELS;
	mOutputParameters.sampleFormat = paFloat32;
	mOutputParameters.suggestedLatency = Pa_GetDeviceInfo(mOutputParameters.device)->defaultLowOutputLatency;
	mOutputParameters.hostApiSpecificStreamInfo = NULL;
}

void	SoundOutputDevice::playSound(float *sound, int seconds) {
	SoundOutputDevice::OutputData	data;

	data.frameIndex = 0;
	data.maxFrameIndex = seconds * SoundOutputDevice::SAMPLE_RATE;

	int nbSamples = data.maxFrameIndex * SoundOutputDevice::NB_CHANNELS;
	data.recordedSamples = sound;

	PaStream *stream;
	if (Pa_OpenStream(&stream, NULL, &mOutputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, SoundOutputDevice::playCallback, &data) != paNoError)
		throw new SoundDeviceException("fail Pa_OpenStream");

	if (Pa_StartStream(stream) != paNoError)
		throw new SoundDeviceException("fail Pa_StartStream");

	while (Pa_IsStreamActive(stream) == 1)
		Pa_Sleep(1000);

	if (Pa_CloseStream(stream) != paNoError)
		throw new SoundDeviceException("fail Pa_StopStream");
}

int	SoundOutputDevice::playCallback(const void */*inputBuffer*/, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo */*timeInfo*/, PaStreamCallbackFlags /*statusFlags*/, void *userData) {
	SoundOutputDevice::OutputData *data = (SoundOutputDevice::OutputData *)userData;
	float *rptr = &data->recordedSamples[data->frameIndex * SoundOutputDevice::NB_CHANNELS];
	float *wptr = (float *)outputBuffer;
	unsigned int i;
	unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;

	if (framesLeft < framesPerBuffer) {
		for (i = 0; i<framesLeft; i++) {
			*wptr++ = *rptr++;
			if (SoundOutputDevice::NB_CHANNELS == 2)
				*wptr++ = *rptr++;
		}
		for (; i < framesPerBuffer; i++) {
			*wptr++ = 0;
			if (SoundOutputDevice::NB_CHANNELS == 2)
				*wptr++ = 0;
		}

		data->frameIndex += framesLeft;

		return paComplete;
	}
	else {
		for (i = 0; i < framesPerBuffer; i++) {
			*wptr++ = *rptr++;
			if (SoundOutputDevice::NB_CHANNELS == 2)
				*wptr++ = *rptr++;
		}

		data->frameIndex += framesPerBuffer;

		return paContinue;
	}
}
