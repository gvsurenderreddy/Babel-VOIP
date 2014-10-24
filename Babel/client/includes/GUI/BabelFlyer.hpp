#pragma once

class BabelFlyer
{
	// ctor - dtor
public:
	BabelFlyer(void);
	~BabelFlyer(void);

	// coplien form
private:
	BabelFlyer(const BabelFlyer &) {}
	const BabelFlyer &operator=(const BabelFlyer &) { return *this; }

	// attributes
private:
	//Ui::BabelContactWidget	mUi;
};
