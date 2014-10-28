#pragma once

#include <QPainter>
#include "ui_BabelInscription.h"

class BabelInscription : public QWidget, public Ui_BabelInscription
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelInscription(void);
		~BabelInscription(void);
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

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
