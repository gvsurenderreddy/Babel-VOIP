#pragma once

#include "Contact.hpp"
#include "AudioManager.hpp"
#include "SoundPacketBuilder.hpp"

class CallManager : public QObject {
	Q_OBJECT
	// ctor - dtor
	public:
		CallManager(void);
		~CallManager(void);

	// coplien form
	private:
		CallManager(const CallManager &) : QObject() {}
		const CallManager &operator=(const CallManager &) { return *this; }

	// handle call
	public:
		void			startCall(const Contact &contact);
		void			stopCall(void);

		bool			isInCommunication(void) const;
		const Contact	&getCurrentCalledContact(void) const;

	// attributes
	private:
		bool				mInCommunication;
		Contact				mCurrentCalledContact;
		AudioManager		mAudioManager;
		SoundPacketBuilder	mSoundPacketBuilder;

};
