#include "BabelDialogButton.hpp"

BabelDialogButton::BabelDialogButton()
	: QDialog()
{
	mUi.setupUi(this);
}

BabelDialogButton::~BabelDialogButton()
{
}

void	BabelDialogButton::setMessage(QString const &msg)
{
	mUi.lineEdit->setText(msg);
}
