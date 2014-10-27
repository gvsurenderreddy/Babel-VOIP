#pragma once

#include "ui_BabelMain.h"

class BabelMain : public QWidget, public Ui_BabelMain
{
	// ctor - dtor
	public:
		BabelMain();
		~BabelMain();

	// coplien form
	private:
		BabelMain(const BabelMain &) : QWidget() {}
		const BabelMain &operator=(const BabelMain &) { return *this; }


		// attributes
	private:
		Ui::BabelMain	mUi;

	// methods
	public:
		Ui::BabelMain const	&getUi() const { return mUi; }
};
