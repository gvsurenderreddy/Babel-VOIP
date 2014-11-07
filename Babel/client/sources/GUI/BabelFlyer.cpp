#include <QEvent>
#include <QKeyEvent>
#include "Contact.hpp"
#include "BabelFlyer.hpp"

BabelFlyer::BabelFlyer(void) : QWidget() {
	mUi.setupUi(this);

	mOriginalSize = size();

	// Echo mode for input password
	mUi.pwdEdit->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);

	QObject::connect(mUi.login,		SIGNAL(clicked()),			this, SLOT(onSubmit()));
	QObject::connect(mUi.emailEdit, SIGNAL(returnPressed()),	this, SLOT(onSubmit()));
	QObject::connect(mUi.pwdEdit,	SIGNAL(returnPressed()),	this, SLOT(onSubmit()));
	QObject::connect(mUi.signup,	SIGNAL(clicked()),			this, SLOT(onRegistrationButtonClicked()));
	QObject::connect(mUi.settings,	SIGNAL(clicked()),			this, SLOT(onOptionsButtonClicked()));
}

BabelFlyer::~BabelFlyer(void) {}

void	BabelFlyer::onSubmit(void) {
	Contact contact;

	contact.setAccountName(mUi.emailEdit->text());
	contact.setPassword(mUi.pwdEdit->text());

	emit askForAuthentication(contact);
}

void	BabelFlyer::onRegistrationButtonClicked(void) {
	emit displayRegistration();
}

void	BabelFlyer::onOptionsButtonClicked(void) {
	emit displaySettings();
}

void	BabelFlyer::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QSize	BabelFlyer::minimumSizeHint() const {
	return mOriginalSize;
}
