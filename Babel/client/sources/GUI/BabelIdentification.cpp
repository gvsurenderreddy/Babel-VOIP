#include "BabelIdentification.hpp"

BabelIdentification::BabelIdentification(void)
{
	mUi.setupUi(this);

	// Remove window borders
	// setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	// Echo mode for input password
	mUi.pwdEdit->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);
}

BabelIdentification::~BabelIdentification(void)
{
}
