#include <iostream>
#include "BabelMainWindow.hpp"

using namespace std;

BabelMainWindow::BabelMainWindow(void)
{
	mTimer = new QTimer(this);
	mUi.setupUi(this);
	QObject::connect(mTimer, SIGNAL(timeout()), this, SLOT(close()));
	show();
	mContact.show();
}

BabelMainWindow::~BabelMainWindow(void)
{
	cout << __FUNCTION__ << ": " << __TIMESTAMP__ << endl;
}

void		BabelMainWindow::timeoutOpenContact()
{
	cout << __FUNCTION__ << ": " << __DATE__ << endl;
	close();
	mContact.show();
}
