#include "CallManager.hpp"
#include "SoundPacketBuilder.hpp"
#include "AudioManager.hpp"

CallManager::CallManager(void) : mInCommunication(false) {
	connect(&mSoundPacketBuilder, SIGNAL(receiveSound(const Sound::Encoded &)), &mAudioManager, SLOT(playSound(const Sound::Encoded &)));
	connect(&mAudioManager, SIGNAL(soundAvailable(const Sound::Encoded &)), &mSoundPacketBuilder, SLOT(sendSound(const Sound::Encoded &)));
}

CallManager::~CallManager(void) {
}

void	CallManager::startCall(const Contact &contact) {
	mAudioManager.startRecording();
	mAudioManager.startPlaying();
	mSoundPacketBuilder.acceptPacketsFrom("127.0.0.1", 4243);
	mCurrentCalledContact.setAccountName(contact.getAccountName());
}

void	CallManager::stopCall(void) {
	mAudioManager.stopRecording();
	mAudioManager.stopPlaying();
	mCurrentCalledContact.setAccountName("");
	mSoundPacketBuilder.acceptPacketsFrom("", 0);
}

bool	CallManager::isInCommunication(void) const {
	return mInCommunication;
}

const Contact	&CallManager::getCurrentCalledContact(void) const {
	return mCurrentCalledContact;
}
