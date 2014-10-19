#include "ScopedLock.hpp"
#include "SoundOutputDevice.hpp"
#include "SoundException.hpp"

SoundOutputDevice::SoundOutputDevice(void) {
	if (Pa_Initialize() != paNoError)
		throw new SoundException("fail Pa_Initialize");

	initOutputDevice();
}

SoundOutputDevice::~SoundOutputDevice(void) {
	Pa_Terminate();
}

void	SoundOutputDevice::initOutputDevice(void) {
	mOutputParameters.device = Pa_GetDefaultOutputDevice();
	if (mOutputParameters.device == paNoDevice)
		throw new SoundException("fail Pa_GetDefaultOutputDevice");

	mOutputParameters.channelCount = Sound::NB_CHANNELS;
	mOutputParameters.sampleFormat = paFloat32;
	mOutputParameters.suggestedLatency = Pa_GetDeviceInfo(mOutputParameters.device)->defaultLowOutputLatency;
	mOutputParameters.hostApiSpecificStreamInfo = NULL;
}

void	SoundOutputDevice::startStream(void) {
	if (Pa_OpenStream(&mStream, NULL, &mOutputParameters, Sound::SAMPLE_RATE, Sound::FRAMES_PER_BUFFER, paClipOff, SoundOutputDevice::callback, this) != paNoError)
		throw new SoundException("fail Pa_OpenStream");

	if (Pa_StartStream(mStream) != paNoError)
		throw new SoundException("fail Pa_StartStream");
}

void	SoundOutputDevice::stopStream(void) {
	if (Pa_CloseStream(mStream) != paNoError)
		throw new SoundException("fail Pa_StopStream");
}

ISoundDevice	&SoundOutputDevice::operator<<(const Sound::Decoded &sound) {
	ScopedLock	scopedLock(&mMutex);

	if (sound.buffer) {
		Sound::Decoded *soundCpy = new Sound::Decoded;

		soundCpy->buffer = sound.buffer;
		soundCpy->size = sound.size;
		mBuffers.push_back(soundCpy);
	}

	return *this;
}

ISoundDevice	&SoundOutputDevice::operator>>(Sound::Decoded &sound) {
	ScopedLock	scopedLock(&mMutex);

	if (mBuffers.size()) {
		Sound::Decoded *soundCpy = mBuffers.front();

		sound.buffer = soundCpy->buffer;
		sound.size = soundCpy->size;

		delete soundCpy;
		mBuffers.pop_front();
	}
	else {
		sound.size = 0;
		sound.buffer = NULL;
	}

	return *this;
}

int	SoundOutputDevice::callback(const void *, void *outputBuffer, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *data) {
	SoundOutputDevice *obj = reinterpret_cast<SoundOutputDevice *>(data);
	ScopedLock scopedLock(&obj->mMutex);

	if (obj->mBuffers.size() == 0)
		return paContinue;

	Sound::Decoded	*sound = obj->mBuffers.front();
	float			*wptr = static_cast<float *>(outputBuffer);

	for (int i = 0; i < sound->size; i++)
		*wptr++ = sound->buffer[i];

	delete sound->buffer;
	delete sound;
	obj->mBuffers.pop_front();

	return paContinue;
}