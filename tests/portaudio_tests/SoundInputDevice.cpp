#include "SoundInputDevice.hpp"
#include "SoundDeviceException.hpp"
#include "SoundOutputDevice.hpp"
#include "opus.h"
#include <iostream>

const int SoundInputDevice::SAMPLE_RATE = 48000;
const int SoundInputDevice::NB_CHANNELS = 2;
const int SoundInputDevice::FRAMES_PER_BUFFER = 480;

std::list<float *> buffers;

SoundInputDevice::SoundInputDevice(void)
	: mStream(NULL)
{
	if (Pa_Initialize() != paNoError)
		throw new SoundDeviceException("fail Pa_Initialize");

	initInputDevice();
}

SoundInputDevice::~SoundInputDevice(void) {
	Pa_Terminate();
}


void	SoundInputDevice::initInputDevice(void) {
	mInputParameters.device = Pa_GetDefaultInputDevice();
	if (mInputParameters.device == paNoDevice)
		throw new SoundDeviceException("fail Pa_GetDefaultInputDevice");

	mInputParameters.channelCount = SoundInputDevice::NB_CHANNELS;
	mInputParameters.sampleFormat = paFloat32;
	mInputParameters.suggestedLatency = Pa_GetDeviceInfo(mInputParameters.device)->defaultLowInputLatency;
	mInputParameters.hostApiSpecificStreamInfo = NULL;
}

void	SoundInputDevice::startStream(void) {
	if (Pa_OpenStream(&mStream, &mInputParameters, NULL, SoundInputDevice::SAMPLE_RATE, SoundInputDevice::FRAMES_PER_BUFFER, paClipOff, SoundInputDevice::callback, this) != paNoError)
		throw new SoundDeviceException("fail Pa_OpenStream");

	if (Pa_StartStream(mStream) != paNoError)
		throw new SoundDeviceException("fail Pa_StartStream");
}

void	SoundInputDevice::stopStream(void) {
	if (Pa_CloseStream(mStream) != paNoError)
		throw new SoundDeviceException("fail Pa_StopStream");
}

ISoundDevice	&SoundInputDevice::operator<<(SoundBuffer *soundBuffer) {
	if (soundBuffer)
		mBuffers.push_back(soundBuffer);

	return *this;
}

ISoundDevice	&SoundInputDevice::operator>>(SoundBuffer *&soundBuffer) {
	if (mBuffers.size()) {
		soundBuffer = mBuffers.front();
		mBuffers.pop_front();
	}
	else
		soundBuffer = NULL;

	return *this;
}

int	SoundInputDevice::callback(const void *inputBuffer, void *, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *data) {
	SoundInputDevice *obj = reinterpret_cast<SoundInputDevice *>(data);

	float	*cpyBuffer = new float[framesPerBuffer * SoundInputDevice::NB_CHANNELS];
	std::memcpy(cpyBuffer, inputBuffer, framesPerBuffer * SoundInputDevice::NB_CHANNELS * sizeof(float));

	ISoundDevice::SoundBuffer *buffer = new ISoundDevice::SoundBuffer;
	buffer->sound = cpyBuffer;
	buffer->nbFrames = framesPerBuffer;
	buffer->currentFrame = 0;
	obj->mBuffers.push_back(buffer);

	return paContinue;
}
