#include "BabelMainWindow.hpp"
#include "BabelUpdate.hpp"

BabelUpdate::BabelUpdate(void)
: QWidget()
{
	mUi.setupUi(this);

	mOriginalSize = size();

	mUi.passwordEdit->setEchoMode(QLineEdit::Password);
	mUi.passwordEdit->setInputMethodHints(Qt::ImhHiddenText | Qt::ImhNoPredictiveText | Qt::ImhNoAutoUppercase);

	QObject::connect(mUi.pseudoEdit, SIGNAL(returnPressed()), this, SLOT(onSubmit()));
	QObject::connect(mUi.statutEdit, SIGNAL(returnPressed()), this, SLOT(onSubmit()));
	QObject::connect(mUi.passwordEdit, SIGNAL(returnPressed()), this, SLOT(onSubmit()));
	QObject::connect(mUi.submitButton, SIGNAL(clicked()), this, SLOT(onSubmit()));
	QObject::connect(mUi.back, SIGNAL(clicked()), this, SLOT(onBackButtonPressed()));
}

BabelUpdate::~BabelUpdate(void) {}

void	BabelUpdate::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QSize	BabelUpdate::minimumSizeHint() const {
	return mOriginalSize;
}

void	BabelUpdate::onBackButtonPressed(void) {
	emit exit();
}

void	BabelUpdate::onSubmit(void) {
	Contact contact;

	contact.setPseudo(mUi.pseudoEdit->text());
	contact.setPassword(mUi.passwordEdit->text());
	contact.setStatus(static_cast<Contact::Status>(mUi.statutEdit->currentIndex()));

	emit updateContactInfo(contact);
}
