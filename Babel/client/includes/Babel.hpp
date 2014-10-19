#pragma once

#include <qlist.h>
#include "Contact.hpp"
#include "BabelMainWindow.hpp"
#include "CallManager.hpp"
#include "ServerCommunication.hpp"

class Babel {

	// client state
	enum State {
		CONNECTED,
		NOT_CONNECTED,
		IN_COMMUNICATION
	};

	// ctor - dtor
	public:
		Babel(void);
		~Babel(void);

	// coplien form
	private:
		Babel(const Babel &);
		const Babel &operator=(const Babel &) { return *this; }

	// start
	public:
		void	run(void);

	// attributes
	private:
		Babel::State		mState;
		QList<Contact>		mContacts;
		BabelMainWindow		mMainWindow;
		CallManager			mCallManager;
		ServerCommunication	mServerCommunication;

};
