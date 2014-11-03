#include "BabelInscription.hpp"

BabelInscription::BabelInscription(void)
	: mEmail(""), mPseudo(""), mPwd(""), mIsRegister(false)
{
	mUi.setupUi(this);

	// Remove window borders
	// setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	// Echo mode for input password
	mUi.pwdEdit1->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit1->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);
	mUi.pwdEdit2->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit2->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);

	// Form validation
	QObject::connect(mUi.ok, SIGNAL(clicked()), this, SLOT(formValidation()));
}

BabelInscription::~BabelInscription(void)
{
}

void		BabelInscription::formValidation()
{
	if (mUi.pwdEdit1->text() == mUi.pwdEdit2->text())
	{
		mEmail = mUi.emailEdit->text();
		mPseudo = mUi.pseudoEdit->text();
		mPwd = mUi.pwdEdit1->text();
		mIsRegister = true;
	}
	else
	{
		mPwd = "";
		mIsRegister = false;
	}
}