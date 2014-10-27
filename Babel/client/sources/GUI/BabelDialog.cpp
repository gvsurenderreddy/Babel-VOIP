#include "BabelDialog.hpp"

BabelDialog::BabelDialog()
	: QDialog()
{
	mUi.setupUi(this);
}

BabelDialog::~BabelDialog()
{
}

void	BabelDialog::setMessage(QString const &msg)
{
	mUi.textBrowser->setText(msg);
}
