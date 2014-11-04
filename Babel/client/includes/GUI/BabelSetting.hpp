#pragma once

#include <QPainter>
#include "BabelDialog.hpp"
#include "ui_BabelSetting.h"

class BabelSetting : public QWidget
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelSetting(void);
		~BabelSetting(void);

	// coplien form
	private:
		BabelSetting(const BabelSetting &) : QWidget() {}
		const BabelSetting &operator=(const BabelSetting &) { return *this; }

	// overrides
	public:
		void paintEvent(QPaintEvent *);
		QSize minimumSizeHint() const;

	// attributes
	private:
		Ui::BabelSetting	mUi;
		BabelDialog			mDialog;
		QString				mHost;
		int					mPort;
		QSize				mOriginalSize;

	// methods
	public:
		Ui::BabelSetting const	&getUi() const { return mUi; }
		BabelDialog const		&getDialog() const { return mDialog; }
		QString const			&getHost() const { return mHost; }
		int						getPort() const { return mPort; }

	// slots
	public slots :
		void	getIpPort();
};
