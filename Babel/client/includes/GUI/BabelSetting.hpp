#pragma once

#include "BabelDialog.hpp"
#include "ui_BabelSetting.h"

class BabelSetting : public QWidget, public Ui_BabelSetting
{
	// ctor - dtor
	public:
		BabelSetting(void);
		~BabelSetting(void);

	// coplien form
	private:
		BabelSetting(const BabelSetting &) : QWidget() {}
		const BabelSetting &operator=(const BabelSetting &) { return *this; }

	// attributes
	private:
		Ui::BabelSetting	mUi;
		BabelDialog			mDialog;

	// methods
	public:
		Ui::BabelSetting const	&getUi() const { return mUi; }

	// slots
	public slots :
		void	getIpPort();
};
