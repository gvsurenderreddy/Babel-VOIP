#include "BabelInscription.hpp"

BabelInscription::BabelInscription(void)
	: mEmail(""), mPseudo(""), mPwd(""), mIsRegister(false)
{
	mUi.setupUi(this);

	mOriginalSize = size();

	// Echo mode for input password
	mUi.pwdEdit1->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit1->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);
	mUi.pwdEdit2->setEchoMode(QLineEdit::Password);
	mUi.pwdEdit2->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);

	// Form validation
	QObject::connect(mUi.ok, SIGNAL(clicked()), this, SLOT(formValidation()));

	// trigger enter pressed to clicked
	QObject::connect(mUi.emailEdit, SIGNAL(returnPressed()), mUi.ok, SIGNAL(clicked()));
	QObject::connect(mUi.pseudoEdit, SIGNAL(returnPressed()), mUi.ok, SIGNAL(clicked()));
	QObject::connect(mUi.pwdEdit1, SIGNAL(returnPressed()), mUi.ok, SIGNAL(clicked()));
	QObject::connect(mUi.pwdEdit2, SIGNAL(returnPressed()), mUi.ok, SIGNAL(clicked()));
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

void	BabelInscription::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QSize	BabelInscription::minimumSizeHint() const {
	return mOriginalSize;
}
