#include "CallManager.hpp"
#include "SoundPacketBuilder.hpp"
#include "AudioManager.hpp"
#include "SoundException.hpp"

CallManager::CallManager(void) : mInCommunication(false) {
	connect(&mSoundPacketBuilder, SIGNAL(receiveSound(const Sound::Encoded &)), &mAudioManager, SLOT(playSound(const Sound::Encoded &)));
	connect(&mAudioManager, SIGNAL(soundAvailable(const Sound::Encoded &)), &mSoundPacketBuilder, SLOT(sendSound(const Sound::Encoded &)));
}

CallManager::~CallManager(void) {
}

void	CallManager::startCall(const Contact &contact) {
	mCurrentCalledContact = contact;
	mInCommunication = true;

	try {
		mSoundPacketBuilder.acceptPacketsFrom(contact.getHost());
		mAudioManager.startRecording();
		mAudioManager.startPlaying();
	}
	catch (const SoundException &) {
		ErrorStatus errorStatus;

		errorStatus.setErrorOccurred(true);
		errorStatus.setErrorCode(ErrorStatus::FAIL_INIT_AUDIO);

		emit criticalError(errorStatus);
	}
}

void	CallManager::stopCall(void) {
	mInCommunication = false;

	mAudioManager.stopRecording();
	mAudioManager.stopPlaying();
	mSoundPacketBuilder.acceptPacketsFrom("");

	mCurrentCalledContact.setAccountName("");
}

bool	CallManager::isInCommunication(void) const {
	return mInCommunication;
}

const Contact	&CallManager::getCurrentCalledContact(void) const {
	return mCurrentCalledContact;
}
