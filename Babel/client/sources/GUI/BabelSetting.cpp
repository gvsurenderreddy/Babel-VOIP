#include "BabelMainWindow.hpp"
#include "BabelSetting.hpp"

BabelSetting::BabelSetting(void)
	: QWidget()
{
	mUi.setupUi(this);

	mOriginalSize = size();

	QObject::connect(mUi.connexion, SIGNAL(clicked()), this, SLOT(getIpPort()));

	// trigger enter pressed to clicked
	QObject::connect(mUi.addrEdit, SIGNAL(returnPressed()), mUi.connexion, SIGNAL(clicked()));
	QObject::connect(mUi.portEdit, SIGNAL(returnPressed()), mUi.connexion, SIGNAL(clicked()));

	QObject::connect(mUi.pseudoEdit, SIGNAL(returnPressed()), mUi.ok, SIGNAL(clicked()));
	QObject::connect(mUi.pwdEdit1, SIGNAL(returnPressed()), mUi.ok, SIGNAL(clicked()));
	QObject::connect(mUi.pwdEdit2, SIGNAL(returnPressed()), mUi.ok, SIGNAL(clicked()));
	QObject::connect(mUi.pwdEdit3, SIGNAL(returnPressed()), mUi.ok, SIGNAL(clicked()));
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
