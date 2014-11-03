#include "BabelMainWindow.hpp"
#include "BabelSetting.hpp"

BabelSetting::BabelSetting(void)
	: QWidget()
{
	mUi.setupUi(this);

	// Remove window borders
	// setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

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
