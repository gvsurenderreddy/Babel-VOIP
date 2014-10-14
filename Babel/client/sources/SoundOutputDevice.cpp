#include <iostream>
#include "ScopedLock.hpp"
#include "SoundOutputDevice.hpp"
#include "SoundDeviceException.hpp"

const int SoundOutputDevice::SAMPLE_RATE = 48000;
const int SoundOutputDevice::NB_CHANNELS = 2;
const int SoundOutputDevice::FRAMES_PER_BUFFER = 480;

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

void	SoundOutputDevice::startStream(void) {
	if (Pa_OpenStream(&mStream, NULL, &mOutputParameters, SoundOutputDevice::SAMPLE_RATE, SoundOutputDevice::FRAMES_PER_BUFFER, paClipOff, SoundOutputDevice::callback, this) != paNoError)
		throw new SoundDeviceException("fail Pa_OpenStream");

	if (Pa_StartStream(mStream) != paNoError)
		throw new SoundDeviceException("fail Pa_StartStream");
}

void	SoundOutputDevice::stopStream(void) {
	if (Pa_CloseStream(mStream) != paNoError)
		throw new SoundDeviceException("fail Pa_StopStream");
}

ISoundDevice	&SoundOutputDevice::operator<<(SoundBuffer *soundBuffer) {
	ScopedLock	scopedLock(&mMutex);

	if (soundBuffer)
		mBuffers.push_back(soundBuffer);

	return *this;
}

ISoundDevice	&SoundOutputDevice::operator>>(SoundBuffer *&soundBuffer) {
	ScopedLock	scopedLock(&mMutex);

	if (mBuffers.size()) {
		soundBuffer = mBuffers.front();
		mBuffers.pop_front();
	}
	else
		soundBuffer = NULL;

	return *this;
}

int	SoundOutputDevice::callback(const void *, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *data) {
	SoundOutputDevice *obj = reinterpret_cast<SoundOutputDevice *>(data);

	ScopedLock	scopedLock(&obj->mMutex);

	if (obj->mBuffers.size() == 0)
		return paContinue;

	unsigned int i;
	float *wptr = (float *)outputBuffer;
	ISoundDevice::SoundBuffer *buffer = obj->mBuffers.front();
	unsigned int framesLeft = buffer->nbFrames - buffer->currentFrame;

	if (framesLeft < framesPerBuffer) {
		for (i = 0; i < framesLeft; i++) {
			*wptr++ = buffer->sound[buffer->currentFrame++];
			if (SoundOutputDevice::NB_CHANNELS == 2)
				*wptr++ = buffer->sound[buffer->currentFrame++];
		}
		for (; i < framesPerBuffer; i++) {
			*wptr++ = 0;
			if (SoundOutputDevice::NB_CHANNELS == 2)
				*wptr++ = 0;
		}
	}
	else {
		for (i = 0; i < framesPerBuffer; i++) {
			*wptr++ = buffer->sound[buffer->currentFrame++];
			if (SoundOutputDevice::NB_CHANNELS == 2)
				*wptr++ = buffer->sound[buffer->currentFrame++];
		}
	}

	if (buffer->currentFrame >= buffer->nbFrames)
		obj->mBuffers.pop_front();

	return paContinue;
}
