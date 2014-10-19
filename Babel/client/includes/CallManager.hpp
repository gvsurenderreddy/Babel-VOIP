#pragma once

#include "Contact.hpp"

class CallManager {

	// ctor - dtor
	public:
		CallManager(void);
		~CallManager(void);

	// coplien form
	private:
		CallManager(const CallManager &) {}
		const CallManager &operator=(const CallManager &) { return *this; }

	// handle call
	public:
		void			startCall(const Contact &contact);
		void			stopCall(void);

		bool			isInCommunication(void) const;
		const Contact	&getCurrentCalledContact(void) const;

	// attributes
	private:
		bool	mInCommunication;
		Contact	mCurrentCalledContact;

};
