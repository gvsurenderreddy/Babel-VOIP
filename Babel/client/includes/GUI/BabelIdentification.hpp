#pragma once

#include "ui_BabelIdentification.h"

class BabelIdentification : public QWidget, public Ui_BabelIdentification
{
	// ctor - dtor
	public:
		BabelIdentification(void);
		~BabelIdentification(void);

	// coplien form
	private:
		BabelIdentification(const BabelIdentification &) : QWidget() {}
		const BabelIdentification &operator=(const BabelIdentification &) { return *this; }

	// attributes
	private:
		Ui::BabelIdentification	mUi;

	// methods
	public:
		Ui::BabelIdentification const	&getUi() const { return mUi; }
};
