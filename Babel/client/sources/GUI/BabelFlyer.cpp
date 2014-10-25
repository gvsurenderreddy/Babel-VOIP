#include "BabelFlyer.hpp"

BabelFlyer::BabelFlyer(void)
{
	mUi.setupUi(this);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

BabelFlyer::~BabelFlyer(void)
{
}
