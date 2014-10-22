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
	mCurrentCalledContact = contact;

	mSoundPacketBuilder.acceptPacketsFrom(contact.getHost(), contact.getPort());
	mAudioManager.startRecording();
	mAudioManager.startPlaying();
}

void	CallManager::stopCall(void) {
	mAudioManager.stopRecording();
	mAudioManager.stopPlaying();
	mSoundPacketBuilder.acceptPacketsFrom("", 0);

	mCurrentCalledContact.setAccountName("");
}

bool	CallManager::isInCommunication(void) const {
	return mInCommunication;
}

const Contact	&CallManager::getCurrentCalledContact(void) const {
	return mCurrentCalledContact;
}
