#include "BabelMainWindow.hpp"
#include "BabelSetting.hpp"

BabelSetting::BabelSetting(void)
	: QWidget()
{
	mUi.setupUi(this);

	mOriginalSize = size();

	QObject::connect(mUi.connexion, SIGNAL(clicked()),			this, SLOT(onSubmit()));
	QObject::connect(mUi.addrEdit,	SIGNAL(returnPressed()),	this, SLOT(onSubmit()));
	QObject::connect(mUi.portEdit,	SIGNAL(returnPressed()),	this, SLOT(onSubmit()));
	QObject::connect(mUi.back,		SIGNAL(clicked()),			this, SLOT(onBackButtonPressed()));

}

BabelSetting::~BabelSetting(void) {}

void		BabelSetting::onSubmit(void) {
	emit askForConnection(mUi.addrEdit->text(), mUi.portEdit->text().toInt());
}

void	BabelSetting::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QSize	BabelSetting::minimumSizeHint() const {
	return mOriginalSize;
}

void	BabelSetting::onBackButtonPressed(void) {
	emit exit();
}
