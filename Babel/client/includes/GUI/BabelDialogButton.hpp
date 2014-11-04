#pragma once

#include <QPainter>
#include "ui_BabelDialogButton.h"

class BabelDialogButton : public QDialog
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelDialogButton();
		~BabelDialogButton();

	// painter
	public:
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

	// coplien form
	private:
		BabelDialogButton(const BabelDialogButton &) : QDialog() {}
		const BabelDialogButton &operator=(const BabelDialogButton &) { return *this; }

	// attributes
	private:
		Ui::BabelDialogButton	mUi;

	// methods
	public:
		Ui::BabelDialogButton const	&getUi() const { return mUi; }
		void					setMessage(QString const &msg);
};
