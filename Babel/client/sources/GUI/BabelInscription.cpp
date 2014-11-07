#include "BabelInscription.hpp"
#include "BabelDialog.hpp"

BabelInscription::BabelInscription(void) {
	mUi.setupUi(this);

	mOriginalSize = size();

	// Echo mode for input password
	mUi.password->setEchoMode(QLineEdit::Password);
	mUi.password->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);
	mUi.passwordConfirmation->setEchoMode(QLineEdit::Password);
	mUi.passwordConfirmation->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);

	QObject::connect(mUi.ok,					SIGNAL(clicked()),			this, SLOT(onSubmit()));
	QObject::connect(mUi.emailEdit,				SIGNAL(returnPressed()),	this, SLOT(onSubmit()));
	QObject::connect(mUi.pseudoEdit,			SIGNAL(returnPressed()),	this, SLOT(onSubmit()));
	QObject::connect(mUi.password,				SIGNAL(returnPressed()),	this, SLOT(onSubmit()));
	QObject::connect(mUi.passwordConfirmation,	SIGNAL(returnPressed()),	this, SLOT(onSubmit()));
	QObject::connect(mUi.back, SIGNAL(clicked()), this, SLOT(onBackButtonPressed()));
}

BabelInscription::~BabelInscription(void) {}

void		BabelInscription::onSubmit(void) {
	if (mUi.password->text() == mUi.passwordConfirmation->text()) {
		Contact contact;

		contact.setAccountName(mUi.emailEdit->text());
		contact.setPseudo(mUi.pseudoEdit->text());
		contact.setPassword(mUi.password->text());

		emit askForRegistration(contact);
	}
	else
		emit displayInformation("Le mot de passe et sa confirmation ne sont pas identiques.");
}

void	BabelInscription::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QSize	BabelInscription::minimumSizeHint() const {
	return mOriginalSize;
}

void	BabelInscription::onBackButtonPressed(void) {
	emit exit();
}
