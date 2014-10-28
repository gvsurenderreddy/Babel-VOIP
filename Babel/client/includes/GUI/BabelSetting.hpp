#pragma once

#include <QPainter>
#include "BabelDialog.hpp"
#include "ui_BabelSetting.h"

class BabelSetting : public QWidget, public Ui_BabelSetting
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelSetting(void);
		~BabelSetting(void);
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

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
		BabelDialog const		&getDialog() const { return mDialog; }
		QString const			&getAddr() const { return mAddr; }
		int						getPort() const { return mPort; }

	// slots
	public slots :
		void	getIpPort();
};
