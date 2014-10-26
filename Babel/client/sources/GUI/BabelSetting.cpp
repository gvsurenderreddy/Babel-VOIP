#include "BabelSetting.hpp"

BabelSetting::BabelSetting(void)
{
	mUi.setupUi(this);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

BabelSetting::~BabelSetting(void)
{
}
