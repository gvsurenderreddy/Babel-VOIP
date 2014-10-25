#pragma once

#include "ui_BabelInscription.h"

class BabelInscription : public QWidget, public Ui_BabelInscription
{
	// ctor - dtor
public:
	BabelInscription(void);
	~BabelInscription(void);

	// coplien form
private:
	BabelInscription(const BabelInscription &) : QWidget() {}
	const BabelInscription &operator=(const BabelInscription &) { return *this; }

	// attributes
private:
	Ui::BabelInscription	mUi;

	// methods
public:
	Ui::BabelInscription const	&getUi() const { return mUi; }
};
