#include "BabelDialogButton.hpp"

BabelDialogButton::BabelDialogButton()
	: QDialog()
{
	mUi.setupUi(this);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

BabelDialogButton::~BabelDialogButton()
{
}

void	BabelDialogButton::setMessage(QString const &msg)
{
	mUi.lineEdit->setText(msg);
}
