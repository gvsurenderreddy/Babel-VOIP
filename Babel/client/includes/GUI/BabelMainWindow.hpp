#pragma once

#include <qlist.h>
#include <QTimer>
#include <qstring.h>
#include <QPainter>
#include "Contact.hpp"
#include "BabelContactWidget.hpp"
#include "BabelFlyer.hpp"
#include "BabelIdentification.hpp"
#include "BabelInscription.hpp"
#include "BabelSetting.hpp"
#include "BabelMain.hpp"
#include "qmainwindow.h"
#include "ErrorStatus.hpp"
#include "ui_BabelMainWindow.h"

class BabelMainWindow : public QMainWindow, public Ui_BabelMainWindow {

	Q_OBJECT

	// ctor - dtor
	public:
		BabelMainWindow(void);
		~BabelMainWindow(void);
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

	// coplien form
	private:
		BabelMainWindow(const BabelMainWindow &) : QMainWindow() {}
		const BabelMainWindow &operator=(const BabelMainWindow &) { return *this; }

	// attributes
	private:
		Ui::BabelMainWindow	mUi;
		BabelFlyer			mFlyer;
		BabelIdentification	mLogin;
		BabelInscription	mSignup;
		BabelSetting		mSetting;
		BabelMain			mMain;

	// public slots
	public slots:
		void	updateContactList(const QList<Contact> &contacts);
		void	newContactInvitation(const Contact &contact);
		void	newMessage(const Contact &contact, const QString &message);
		void	newCallInvitation(const Contact &contact);
		void	startingCommunication(const Contact &contact, bool hasAccepted);
		void	terminatingCommunication(const Contact &contact);
		void	updateInfo(const Contact &contact);
		void	createAccountSuccess(const ErrorStatus &errorStatus);
		void	authenticateSuccess(const ErrorStatus &errorStatus);
		void	sendInvitationSuccess(const ErrorStatus &errorStatus);
		void	acceptContactSuccess(const ErrorStatus &errorStatus);
		void	deleteContactSuccess(const ErrorStatus &errorStatus);
		void	disconnectSuccess(const ErrorStatus &errorStatus);
		void	sendMessageSuccess(const ErrorStatus &errorStatus);
		void	updateInfoSuccess(const ErrorStatus &errorStatus);
		void	callContactSuccess(const ErrorStatus &errorStatus);
		void	acceptCallSuccess(const ErrorStatus &errorStatus);
		void	terminateCallSuccess(const ErrorStatus &errorStatus);
		void	connectToServerSuccess(const ErrorStatus &errorStatus);
		void	disconnectedFromServer(void);

	// signals
	signals:
		void	askForRegistration(const Contact &contact);
		void	askForAuthentication(const Contact &contact);
		void	askForAddingContact(const Contact &contact);
		void	askForAcceptingContact(const Contact &contact, bool hasAccepted);
		void	askForDeletingContact(const Contact &contact);
		void	askForSendingMessage(const Contact &contact, const QString &message);
		void	askForDisconnection(void);
		void	askForUpdatingInfo(const Contact &contact);
		void	askForCalling(const Contact &contact);
		void	askForAcceptingCall(const Contact &contact, bool hasAccepted);
		void	askForTerminatingCall(const Contact &contact);
		void	askForConnectionToServer(const QString &addr, int port);

	// member function
	public:
		void	show();

};
