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
	*mOutputDevice << mEncodeManager.decode(sound);
}

void	AudioManager::startRecording(void) {
	mInputDevice->startStream();
	this->start();
}

void	AudioManager::run(void){
	Sound::Decoded sound;

	while (true) {
		*mInputDevice >> sound;

		if (sound.buffer)
			emit AudioManager::soundAvailable(mEncodeManager.encode(sound));
	}
}

void	AudioManager::stopRecording(void) {
	this->exit();
	mInputDevice->stopStream();
}

void	AudioManager::startPlaying(void) {
	mOutputDevice->startStream();
}

void	AudioManager::stopPlaying(void) {
	mOutputDevice->stopStream();
}
