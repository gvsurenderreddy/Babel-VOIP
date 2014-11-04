#include <QEvent>
#include <QKeyEvent>
#include "BabelFlyer.hpp"

BabelFlyer::BabelFlyer(void)
	: QWidget()
{
	mUi.setupUi(this);

	mOriginalSize = size();

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

void	BabelFlyer::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QSize	BabelFlyer::minimumSizeHint() const {
	return mOriginalSize;
}
