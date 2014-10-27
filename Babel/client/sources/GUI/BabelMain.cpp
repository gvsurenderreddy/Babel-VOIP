#include "BabelMain.hpp"

BabelMain::BabelMain()
	: QWidget()
{
	mUi.setupUi(this);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

BabelMain::~BabelMain()
{

}