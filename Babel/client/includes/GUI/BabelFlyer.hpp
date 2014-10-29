#pragma once

#include <QPainter>
#include "ui_BabelFlyer.h"

class BabelFlyer : public QWidget, public Ui_BabelFlyer
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelFlyer(void);
		~BabelFlyer(void);
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

	// coplien form
	private:
		BabelFlyer(const BabelFlyer &) : QWidget() {}
		const BabelFlyer &operator=(const BabelFlyer &) { return *this; }

	// attributes
	private:
		Ui::BabelFlyer	mUi;

	// methods
	public:
		Ui::BabelFlyer const	&getUi() const { return mUi; }
		QString const			&getEmail() const { return mUi.emailEdit->text(); }
		QString const			&getPwd() const { return mUi.pwdEdit->text(); }
};
