#include "AudioManager.hpp"
#include "SoundInputDevice.hpp"
#include "SoundOutputDevice.hpp"

AudioManager::AudioManager(void)
: mInputDevice(NULL), mOutputDevice(NULL), mRecordEnable(false), mPlayEnable(false)
{
	mInputDevice = new SoundInputDevice;
	mInputDevice->setOnSoundDeviceEventListener(this);

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
}

void	AudioManager::onSoundAvailable(ISoundDevice *) {
	Sound::Decoded sound;

	*mInputDevice >> sound;
	if (sound.buffer)
		emit AudioManager::soundAvailable(mEncodeManager.encode(sound));
}

void	AudioManager::stopRecording(void) {
	mInputDevice->stopStream();
}

void	AudioManager::startPlaying(void) {
	mOutputDevice->startStream();
}

void	AudioManager::stopPlaying(void) {
	mOutputDevice->stopStream();
}
