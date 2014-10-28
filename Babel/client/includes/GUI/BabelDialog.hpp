#pragma once

#include <QPainter>
#include "ui_BabelDialog.h"

class BabelDialog : public QDialog
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelDialog();
		~BabelDialog();
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

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
