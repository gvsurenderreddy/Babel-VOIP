#pragma once

#include <QPainter>
#include "ui_BabelMain.h"
#include "ContactListModel.hpp"
#include "MessageListModel.hpp"
#include "BabelDialog.hpp"

class BabelMain : public QWidget, public Ui_BabelMain
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelMain();
		~BabelMain();
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

	// coplien form
	private:
		BabelMain(const BabelMain &) : QWidget() {}
		const BabelMain &operator=(const BabelMain &) { return *this; }


	// attributes
	private:
		Ui::BabelMain		mUi;
		QString				mNewContact;
		ContactListModel	*mModel;
		MessageListModel	*mMessages;
		BabelDialog			mDialog;
		Contact				mCurrentContact;
		Contact				mContactInCall;
		bool				mIsCall;

	// methods
	public:
		Ui::BabelMain const	&getUi() const { return mUi; }
		QString const		&getNewContact() const { return mNewContact; }
		ContactListModel	*getModel() const { return mModel; }
		MessageListModel	*getMessages() const { return mMessages; }
		Contact const		&getCurrentContact() const { return mCurrentContact; }
		Contact const		&getContactInCall() const { return mContactInCall; }
		bool				getIsCall() const { return mIsCall; }
		void				setCurrentContact(Contact const &contact) { mCurrentContact = contact; }
		void				setContactInCall(Contact const &contact) { mContactInCall = contact; }
		void				setIsCall(bool isCall) { mIsCall = isCall; }
		BabelDialog 		&getDialog() { return mDialog; }

	// slots
	public slots :
		void		onClickContact(QModelIndex const &index);
		void		onClickAddContact();
};
