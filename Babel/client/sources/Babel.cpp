#include <QMetaType>
#include <iostream>
#include "Sound.hpp"
#include "Babel.hpp"

Babel::Babel(void) {
	qRegisterMetaType<Sound::Encoded>();

	connect(&mServerCommunication, SIGNAL(receiveContactInfo(const Contact &)),									this,			SLOT(receiveContactInfo(const Contact &)));
	connect(&mServerCommunication, SIGNAL(receiveContactInvitation(const Contact &)),							&mMainWindow,	SLOT(newContactInvitation(const Contact &)));
	connect(&mServerCommunication, SIGNAL(receiveContactDeletion(const Contact &)),								this,			SLOT(receiveContactDeletion(const Contact &)));
	connect(&mServerCommunication, SIGNAL(receiveMessage(const Contact &, const QString &)),					&mMainWindow,	SLOT(newMessage(const Contact &, const QString &)));
	connect(&mServerCommunication, SIGNAL(receiveCallInvitation(const Contact &)),								&mMainWindow,	SLOT(newCallInvitation(const Contact &)));
	connect(&mServerCommunication, SIGNAL(receiveCallAnswer(const Contact &, bool)),							this,			SLOT(receiveCallAnswer(const Contact &, bool)));
	connect(&mServerCommunication, SIGNAL(receiveCallClose(const Contact &)),									this,			SLOT(receiveCallClose(const Contact &)));
	connect(&mServerCommunication, SIGNAL(receiveCallAnswer(const Contact &, bool)),							&mMainWindow,	SLOT(startingCommunication(const Contact &, bool)));
	connect(&mServerCommunication, SIGNAL(receiveCallClose(const Contact &)),									&mMainWindow,	SLOT(terminatingCommunication(const Contact &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForRegistration(const ErrorStatus &)),				&mMainWindow,	SLOT(createAccountSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForAuthentication(const ErrorStatus &)),			&mMainWindow,	SLOT(authenticateSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForAuthentication(const ErrorStatus &)),			this,			SLOT(receiveServerAnswerForAuthentication(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForAddingContact(const ErrorStatus &)),			&mMainWindow,	SLOT(sendInvitationSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForAcceptingContact(const ErrorStatus &)),			&mMainWindow,	SLOT(acceptContactSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForDeletingContact(const ErrorStatus &)),			&mMainWindow,	SLOT(deleteContactSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForDisconnecting(const ErrorStatus &)),			this,			SLOT(receiveServerAnswerForDisconnecting(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForDisconnecting(const ErrorStatus &)),			&mMainWindow,	SLOT(disconnectSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForUpdatingInfo(const ErrorStatus &)),				&mMainWindow,	SLOT(updateInfoSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForSendingMessage(const ErrorStatus &)),			&mMainWindow,	SLOT(sendMessageSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForCallingContact(const ErrorStatus &)),			&mMainWindow,	SLOT(callContactSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForAcceptingCallInvitation(const ErrorStatus &)),	&mMainWindow,	SLOT(acceptCallSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveServerAnswerForTerminatingCall(const ErrorStatus &)),			&mMainWindow,	SLOT(terminateCallSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(receiveAnswerForConnectionToServer(const ErrorStatus &)),				&mMainWindow,	SLOT(connectToServerSuccess(const ErrorStatus &)));
	connect(&mServerCommunication, SIGNAL(disconnectedFromServer()),											&mMainWindow,	SLOT(disconnectedFromServer()));

	connect(&mMainWindow, SIGNAL(askForRegistration(const Contact &)),						&mServerCommunication,	SLOT(createAccount(const Contact &)));
	connect(&mMainWindow, SIGNAL(askForAuthentication(const Contact &)),					this,					SLOT(askForAuthentication(const Contact &)));
	connect(&mMainWindow, SIGNAL(askForAuthentication(const Contact &)),					&mServerCommunication,	SLOT(authenticate(const Contact &)));
	connect(&mMainWindow, SIGNAL(askForAddingContact(const Contact &)),						&mServerCommunication,	SLOT(addContact(const Contact &)));
	connect(&mMainWindow, SIGNAL(askForAcceptingContact(const Contact &, bool)),			&mServerCommunication,	SLOT(acceptContactInvitation(const Contact &, bool)));
	connect(&mMainWindow, SIGNAL(askForDeletingContact(const Contact &)),					&mServerCommunication,	SLOT(deleteContact(const Contact &)));
	connect(&mMainWindow, SIGNAL(askForSendingMessage(const Contact &, const QString &)),	&mServerCommunication,	SLOT(sendMessage(const Contact &, const QString &)));
	connect(&mMainWindow, SIGNAL(askForDisconnection(void)),								&mServerCommunication,	SLOT(disconnect(void)));
	connect(&mMainWindow, SIGNAL(askForUpdatingInfo(const Contact &)),						&mServerCommunication,	SLOT(updateInfo(const Contact &)));
	connect(&mMainWindow, SIGNAL(askForCalling(const Contact &)),							&mServerCommunication,	SLOT(call(const Contact &)));
	connect(&mMainWindow, SIGNAL(askForAcceptingCall(const Contact &, bool)),				&mServerCommunication,	SLOT(acceptCallInvitation(const Contact &, bool)));
	connect(&mMainWindow, SIGNAL(askForTerminatingCall(const Contact &)),					&mServerCommunication,	SLOT(terminateCall(const Contact &)));
	connect(&mMainWindow, SIGNAL(askForConnectionToServer(const QString &, int)),			&mServerCommunication,	SLOT(connectToServer(const QString &, int)));

	connect(&mCallManager, SIGNAL(criticalError(const ErrorStatus &)), this, SLOT(criticalErrorHappenedInCallManager(const ErrorStatus &)));
}

Babel::~Babel(void) {
}

void	Babel::run(void) {
	mMainWindow.show();
}

void	Babel::receiveContactInfo(const Contact &contact) {
	if (contact.getAccountName() == mLoggedUser.getAccountName()) {
		mLoggedUser = contact;
		mMainWindow.updateInfo(contact);
	}
	else {
		QList<Contact>::iterator it = mContacts.begin();
		QList<Contact>::iterator end = mContacts.end();

		// AMELIORER AVEC UN FIND!!!
		while (it != end) {
			if (it->getAccountName() == contact.getAccountName()) {
				*it = contact;
				mMainWindow.updateContactList(mContacts);
				return ;
			}
			it++;
		}

		mContacts.push_back(contact);
		mMainWindow.updateContactList(mContacts);
	}
}

void	Babel::receiveContactDeletion(const Contact &contact) {
	QList<Contact>::iterator it = mContacts.begin();
	QList<Contact>::iterator end = mContacts.end();

	while (it != end) {
		if (it->getAccountName() == contact.getAccountName())
			it = mContacts.erase(it);
		else
			it++;
	}

	mMainWindow.updateContactList(mContacts);
}

void	Babel::receiveCallAnswer(const Contact &contact, bool hasAccept) {
	if (hasAccept)
		mCallManager.startCall(contact);
}

void	Babel::receiveCallClose(const Contact &contact) {
	if (mCallManager.getCurrentCalledContact().getAccountName() == contact.getAccountName())
		mCallManager.stopCall();
}

void	Babel::receiveServerAnswerForDisconnecting(const ErrorStatus &errorStatus) {
	if (errorStatus.errorOccurred() == false && mCallManager.isInCommunication())
		mCallManager.stopCall();
}

void	Babel::askForAuthentication(const Contact &contact) {
	mLoggedUser = contact;
}

void	Babel::criticalErrorHappenedInCallManager(const ErrorStatus &errorStatus) {
	if (errorStatus.getErrorCode() == ErrorStatus::FAIL_INIT_SOCKET) {
		std::cout << "critical error during UDP socket initialization" << std::endl;;
		exit(0);
	}
	else
		mServerCommunication.terminateCall(mCallManager.getCurrentCalledContact());
}

void	Babel::receiveServerAnswerForAuthentication(const ErrorStatus &errorStatus) {
	if (errorStatus.errorOccurred() == false)
		mServerCommunication.getContactInfo(mLoggedUser);
}
