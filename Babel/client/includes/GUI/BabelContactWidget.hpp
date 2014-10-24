#pragma once

#include "qmainwindow.h"
#include "ui_BabelContactWidget.h"

class BabelContactWidget : public QWidget, public Ui_BabelContactWidget
{
	// ctor - dtor
	public:
	BabelContactWidget(void);
	~BabelContactWidget(void);

	// coplien form
	private:
	BabelContactWidget(const BabelContactWidget &) : QWidget() {}
	const BabelContactWidget &operator=(const BabelContactWidget &) { return *this; }

	// attributes
	private:
	Ui::BabelContactWidget	mUi;
};
