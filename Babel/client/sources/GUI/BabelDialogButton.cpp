#include "BabelDialogButton.hpp"

BabelDialogButton::BabelDialogButton()
	: QDialog(), mHasAccepted(false)
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

void	BabelDialogButton::setHasAccepted(bool hasAccepted)
{
	mHasAccepted = hasAccepted;
}
