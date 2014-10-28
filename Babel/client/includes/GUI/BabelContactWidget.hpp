#pragma once

#include <QPainter>
#include "qmainwindow.h"
#include "ui_BabelContactWidget.h"

class BabelContactWidget : public QWidget, public Ui_BabelContactWidget
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelContactWidget(void);
		~BabelContactWidget(void);
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

	// coplien form
	private:
		BabelContactWidget(const BabelContactWidget &) : QWidget() {}
		const BabelContactWidget &operator=(const BabelContactWidget &) { return *this; }

	// attributes
	private:
		Ui::BabelContactWidget	mUi;
};
