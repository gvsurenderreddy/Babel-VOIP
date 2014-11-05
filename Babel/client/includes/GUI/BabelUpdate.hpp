#pragma once

#include <QPainter>
#include "BabelDialog.hpp"
#include "ui_BabelUpdate.h"
#include "Contact.hpp"

class BabelUpdate : public QWidget
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelUpdate(void);
		~BabelUpdate(void);

	// coplien form
	private:
		BabelUpdate(const BabelUpdate &) : QWidget() {}
		const BabelUpdate &operator=(const BabelUpdate &) { return *this; }

	// overrides
	public:
		void paintEvent(QPaintEvent *);
		QSize minimumSizeHint() const;

	// intern slots
	private slots:
		void	onBackButtonPressed(void);
		void	onSubmit(void);

	// signals
	signals:
		void	exit(void);
		void	updateContactInfo(Contact &contact);

	// attributes
	private:
		Ui::BabelUpdate		mUi;
		QSize				mOriginalSize;

};
