#pragma once

#include <QPainter>
#include "ui_BabelIdentification.h"

class BabelIdentification : public QWidget, public Ui_BabelIdentification
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelIdentification(void);
		~BabelIdentification(void);
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

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
