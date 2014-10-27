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
		QString				mAddr;
		int					mPort;

	// methods
	public:
		Ui::BabelSetting const	&getUi() const { return mUi; }
		QString const			&getAddr() const { return mAddr; }
		int						getPort() const { return mPort; }

	// slots
	public slots :
		void	getIpPort();
};
