#pragma once

#include "ui_BabelDialog.h"

class BabelDialog : public QDialog
{
	// ctor - dtor
	public:
		BabelDialog();
		~BabelDialog();

	// coplien form
	private:
		BabelDialog(const BabelDialog &) : QDialog() {}
		const BabelDialog &operator=(const BabelDialog &) { return *this; }

	// attributes
	private:
		Ui::BabelDialog	mUi;

	// methods
	public:
		Ui::BabelDialog const	&getUi() const { return mUi; }
		void					setMessage(QString const &msg);
};
