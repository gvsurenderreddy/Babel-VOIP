#pragma once

#include <QTimer>
#include "BabelContactWidget.hpp"
#include "qmainwindow.h"
#include "ui_BabelMainWindow.h"

class BabelMainWindow : public QMainWindow, public Ui_BabelMainWindow
{
	// ctor - dtor
	public:
		BabelMainWindow(void);
		~BabelMainWindow(void);

	// coplien form
	private:
		BabelMainWindow(const BabelMainWindow &) {}
		const BabelMainWindow &operator=(const BabelMainWindow &) { return *this; }

	// attributes
	private:
		Ui::BabelMainWindow	mUi;
		BabelContactWidget	mContact;
		QTimer				*mTimer;

	// slots
	public slots:
		void	timeoutOpenContact();

	// member function
	public:
		virtual void	show();
};
