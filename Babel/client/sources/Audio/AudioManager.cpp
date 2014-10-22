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
	Sound::Decoded input;
	input = mEncodeManager.decode(sound);
	*mOutputDevice << input;
}

void	AudioManager::startRecording(void) {
	mInputDevice->startStream();
	this->start();
}

void	AudioManager::run(void){
	Sound::Decoded sound;
	Sound::Encoded input;

	while (true){
		*mInputDevice >> sound;
		if (sound.buffer){
			input = mEncodeManager.encode(sound);
			emit AudioManager::soundAvailable(input);
		}
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
