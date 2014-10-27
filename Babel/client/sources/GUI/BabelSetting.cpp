#include "BabelMainWindow.hpp"
#include "BabelSetting.hpp"

BabelSetting::BabelSetting(void)
	: QWidget()
{
	mUi.setupUi(this);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	QObject::connect(mUi.connexion, SIGNAL(clicked()), &mDialog, SLOT(show()));
	QObject::connect(mUi.connexion, SIGNAL(clicked()), this, SLOT(getIpPort()));
}

BabelSetting::~BabelSetting(void)
{

}

void		BabelSetting::getIpPort()
{
	mAddr = mUi.addrEdit->text();
	mPort = mUi.portEdit->text().toInt();

	QString	text("address: " + mAddr + "\nport: " + QString::number(mPort));
	(&mDialog)->getUi().textBrowser->setText(QApplication::translate("BabelDialogClass", text.toStdString().c_str(), 0));
}
