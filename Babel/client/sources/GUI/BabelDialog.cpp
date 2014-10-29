#include "BabelDialog.hpp"

BabelDialog::BabelDialog()
	: QDialog()
{
	mUi.setupUi(this);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

BabelDialog::~BabelDialog()
{
}

void	BabelDialog::setMessage(QString const &msg)
{
	mUi.textBrowser->setText(msg);
}
