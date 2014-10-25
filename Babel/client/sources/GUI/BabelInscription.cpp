#include "BabelInscription.hpp"

BabelInscription::BabelInscription(void)
{
	mUi.setupUi(this);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	// Echo mode for input password
	mUi.pwdEdit1->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit1->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);
	mUi.pwdEdit2->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit2->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);
}

BabelInscription::~BabelInscription(void)
{
}
