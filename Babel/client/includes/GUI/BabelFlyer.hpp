#pragma once

#include "ui_BabelFlyer.h"

class BabelFlyer : public QWidget, public Ui_BabelFlyer
{
	// ctor - dtor
	public:
	BabelFlyer(void);
	~BabelFlyer(void);

	// coplien form
	private:
	BabelFlyer(const BabelFlyer &) : QWidget() {}
	const BabelFlyer &operator=(const BabelFlyer &) { return *this; }

	// attributes
	private:
	Ui::BabelFlyer	mUi;

	// methods
	public:
	Ui::BabelFlyer const	&getUi() const { return mUi; }
};
