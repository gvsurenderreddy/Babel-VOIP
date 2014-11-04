#pragma once

#include <QPainter>
#include "ui_BabelInscription.h"

class BabelInscription : public QWidget
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelInscription(void);
		~BabelInscription(void);

	// overrides
	public:
		void paintEvent(QPaintEvent *);
		QSize minimumSizeHint() const;

	// coplien form
	private:
		BabelInscription(const BabelInscription &) : QWidget() {}
		const BabelInscription &operator=(const BabelInscription &) { return *this; }

	// attributes
	private:
		Ui::BabelInscription	mUi;
		QString					mEmail;
		QString					mPseudo;
		QString					mPwd;
		bool					mIsRegister;
		QSize			mOriginalSize;

	// methods
	public:
		Ui::BabelInscription const	&getUi() const { return mUi; }
		QString const				&getEmail() const { return mEmail; }
		QString const				&getPseudo() const { return mPseudo; }
		QString const				&getPwd() const { return mPwd; }
		bool						getIsRegister() const { return mIsRegister; }

		void						setIsRegister(bool isRegister) { mIsRegister = isRegister; }

	// slots
	public slots:
		void					formValidation();
};
