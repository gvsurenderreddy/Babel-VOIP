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
		QSize				mOriginalSize;

	// slots
	public slots :
		void	onSubmit(void);
		void	onBackButtonPressed(void);

	// signals
	signals:
		void	askForConnection(const QString &host, int port);
		void	exit(void);

};
