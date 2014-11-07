#pragma once

#include <QPainter>
#include "ui_BabelMain.h"
#include "ContactListModel.hpp"
#include "MessageListModel.hpp"
#include "BabelDialog.hpp"

class BabelMain : public QWidget
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelMain();
		~BabelMain();

	// coplien form
	private:
		BabelMain(const BabelMain &) : QWidget() {}
		const BabelMain &operator=(const BabelMain &) { return *this; }

	// overrides
	public:
		void paintEvent(QPaintEvent *);
		QSize minimumSizeHint() const;

	// attributes
	private:
		Ui::BabelMain		mUi;
		ContactListModel	*mModel;
		MessageListModel	*mMessages;
		Contact				mCurrentContact;
		Contact				mContactInCall;
		Contact				mUser;
		bool				mIsCall;
		QSize				mOriginalSize;

	//public slots
	public slots:
		void	setContactList(const QList<Contact> &contacts);
		void	receiveMessage(const Contact &contact, const QString &message);
		void	startCommunication(const Contact &contact, bool hasAccepted);
		void	terminateCommunication(const Contact &contact);
		void	setUser(const Contact &contact);

	// intern slots
	private slots:
		void	onClickContact(QModelIndex const &index);
		void	onOptionsButtonClicked(void);
		void	onAddContactButtonClicked(void);
		void	onDeleteContactButtonClicked(void);
		void	onSendButtonClicked(void);
		void	onCallButtonClicked(void);
		void	onLogoutButtonClicked(void);

	// signals
	signals:
		void	updateContactInfo(void);
		void	addContact(const Contact &contact);
		void	deleteContact(const Contact &contact);
		void	sendMessage(const Contact &contact, const QString &message);
		void	callContact(const Contact &contact);
		void	closeCall(const Contact &contact);
		void	logout(void);
		void	displayInformation(const QString &message);

};
