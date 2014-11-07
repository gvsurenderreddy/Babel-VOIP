#pragma once

#include <QPainter>
#include "Contact.hpp"
#include "ui_BabelInscription.h"

class BabelInscription : public QWidget
{
	Q_OBJECT

	// ctor - dtor
	public:
		BabelInscription(void);
		~BabelInscription(void);

	// overrides
	public:
		void paintEvent(QPaintEvent *);
		QSize minimumSizeHint() const;

	// coplien form
	private:
		BabelInscription(const BabelInscription &) : QWidget() {}
		const BabelInscription &operator=(const BabelInscription &) { return *this; }

	// attributes
	private:
		Ui::BabelInscription	mUi;
		QSize					mOriginalSize;

	// slots
	public slots:
		void	onSubmit(void);
		void	onBackButtonPressed(void);

	// signals
	signals:
		void	askForRegistration(const Contact &contact);
		void	exit(void);
		void	displayInformation(const QString &message);

};
