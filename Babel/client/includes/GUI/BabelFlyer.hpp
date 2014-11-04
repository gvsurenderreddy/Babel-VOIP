#pragma once

#include <QPainter>
#include "ui_BabelFlyer.h"

class BabelFlyer : public QWidget
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelFlyer(void);
		~BabelFlyer(void);

	// overrides
	public:
		void paintEvent(QPaintEvent *);
		QSize minimumSizeHint() const;

	// coplien form
	private:
		BabelFlyer(const BabelFlyer &) : QWidget() {}
		const BabelFlyer &operator=(const BabelFlyer &) { return *this; }

	// attributes
	private:
		Ui::BabelFlyer	mUi;
		QString			mEmail;
		QString			mPwd;
		bool			mIsAuthenticate;
		QSize			mOriginalSize;

	// methods
	public:
		Ui::BabelFlyer const	&getUi() const { return mUi; }
		QString const			&getEmail() const { return mEmail; }
		QString const			&getPwd() const { return mPwd; }
		bool					getIsAuthenticate() const { return mIsAuthenticate; }

		void					setIsAuthenticate(bool isAuthenticate) { mIsAuthenticate = isAuthenticate; }

	// slots
	public slots:
		void			authenticateValidation();
};
