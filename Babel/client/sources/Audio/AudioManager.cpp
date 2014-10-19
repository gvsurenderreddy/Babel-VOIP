#include "AudioManager.hpp"
#include "SoundInputDevice.hpp"
#include "SoundOutputDevice.hpp"

AudioManager::AudioManager(void)
: mInputDevice(NULL), mOutputDevice(NULL), mRecordEnable(false), mPlayEnable(false)
{
	mInputDevice = new SoundInputDevice;
	mOutputDevice = new SoundOutputDevice;
}

AudioManager::~AudioManager(void) {
	if (mInputDevice)
		delete mInputDevice;

	if (mOutputDevice)
		delete mOutputDevice;
}

void	AudioManager::playSound(const Sound::Encoded &sound) {
}

void	AudioManager::startRecording(void) {
}

void	AudioManager::stopRecording(void) {
}

void	AudioManager::startPlaying(void) {
}

void	AudioManager::stopPlaying(void) {
}
