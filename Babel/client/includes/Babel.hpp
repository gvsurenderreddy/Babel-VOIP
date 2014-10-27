#pragma once

#include <qlist.h>
#include <qobject.h>
#include "Contact.hpp"
#include "BabelMainWindow.hpp"
#include "CallManager.hpp"
#include "ServerCommunication.hpp"

class Babel : public QObject {

	Q_OBJECT

	// ctor - dtor
	public:
		Babel(void);
		~Babel(void);

	// coplien form
	private:
		Babel(const Babel &) : QObject() {}
		const Babel &operator=(const Babel &) { return *this; }

	// start
	public:
		void	run(void);

	// slots
	private slots:
		void	receiveContactInfo(const Contact &contact);
		void	receiveContactDeletion(const Contact &contact);
		void	receiveCallAnswer(const Contact &contact, bool hasAccept);
		void	receiveCallClose(const Contact &contact);
		void	receiveServerAnswerForDisconnecting(const ErrorStatus &errorStatus);
		void	askForAuthentication(const Contact &contact);

	// attributes
	private:
		Contact				mLoggedUser;
		QList<Contact>		mContacts;
		BabelMainWindow		mMainWindow;
		CallManager			mCallManager;
		ServerCommunication	mServerCommunication;

};
