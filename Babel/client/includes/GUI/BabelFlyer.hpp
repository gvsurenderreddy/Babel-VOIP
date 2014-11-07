#pragma once

#include <QPainter>
#include "ui_BabelFlyer.h"
#include "Contact.hpp"

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
		QSize			mOriginalSize;

	// slots
	public slots:
		void	onSubmit(void);
		void	onOptionsButtonClicked(void);
		void	onRegistrationButtonClicked(void);

	// signals
	signals:
		void	askForAuthentication(const Contact &user);
		void	displaySettings(void);
		void	displayRegistration(void);

};
