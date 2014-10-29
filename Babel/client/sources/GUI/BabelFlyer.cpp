#include "BabelFlyer.hpp"

BabelFlyer::BabelFlyer(void)
	: QWidget()
{
	mUi.setupUi(this);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	// Echo mode for input password
	mUi.pwdEdit->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);

	QObject::connect(mUi.login, SIGNAL(clicked()), this, SLOT(authenticateValidation()));
}

BabelFlyer::~BabelFlyer(void)
{
}

void			BabelFlyer::authenticateValidation()
{
	mEmail = mUi.emailEdit->text();
	mPwd = mUi.pwdEdit->text();
}
