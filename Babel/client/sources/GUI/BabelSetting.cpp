#include "BabelMainWindow.hpp"
#include "BabelSetting.hpp"

BabelSetting::BabelSetting(void)
	: QWidget()
{
	mUi.setupUi(this);

	mOriginalSize = size();

	QObject::connect(mUi.connexion, SIGNAL(clicked()), this, SLOT(getIpPort()));
}

BabelSetting::~BabelSetting(void)
{

}

void		BabelSetting::getIpPort()
{
	mHost = mUi.addrEdit->text();
	mPort = mUi.portEdit->text().toInt();
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
