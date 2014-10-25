#pragma once

#include <QTimer>
#include "BabelContactWidget.hpp"
#include "BabelFlyer.hpp"
#include "BabelIdentification.hpp"
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
	BabelMainWindow(const BabelMainWindow &) : QMainWindow() {}
	const BabelMainWindow &operator=(const BabelMainWindow &) { return *this; }

	// attributes
private:
	Ui::BabelMainWindow	mUi;
	BabelFlyer			mFlyer;
	BabelIdentification	mConnexion;

	// methods
public:
	virtual void	show();
};
