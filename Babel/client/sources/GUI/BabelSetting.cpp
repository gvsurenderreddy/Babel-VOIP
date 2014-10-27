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
	QString	addr(mUi.addrEdit->text());
	QString port(mUi.portEdit->text());

	QString	text("address: " + addr + "\nport: " + port);
	(&mDialog)->getUi().textBrowser->setText(QApplication::translate("BabelDialogClass", text.toStdString().c_str(), 0));
}
