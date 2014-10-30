#pragma once

#include <QPainter>
#include "ui_BabelMain.h"
#include "ContactListModel.hpp"
#include "BabelDialog.hpp"

class BabelMain : public QWidget, public Ui_BabelMain
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelMain();
		~BabelMain();
		void paintEvent(QPaintEvent *)
		{
			QStyleOption opt;
			opt.init(this);
			QPainter p(this);
			style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		}

	// coplien form
	private:
		BabelMain(const BabelMain &) : QWidget() {}
		const BabelMain &operator=(const BabelMain &) { return *this; }


	// attributes
	private:
		Ui::BabelMain		mUi;
		ContactListModel	*mModel;
		BabelDialog			mDialog;

	// methods
	public:
		Ui::BabelMain const	&getUi() const { return mUi; }
		ContactListModel	*getModel() const { return mModel; }

	// slots
	public slots :
		void		onClickContact(QModelIndex const &index);
};
