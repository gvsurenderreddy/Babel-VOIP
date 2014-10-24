#include <iostream>
#include "BabelMainWindow.hpp"

using namespace std;

BabelMainWindow::BabelMainWindow(void)
{
	mTimer = new QTimer(this);
	mUi.setupUi(this);
	QObject::connect(mTimer, SIGNAL(timeout()), this, SLOT(close()));
}

BabelMainWindow::~BabelMainWindow(void)
{
	cout << __FUNCTION__ << endl;
}

void		BabelMainWindow::show()
{
	cout << __FUNCTION__ << endl;
	mTimer->start(1024);
	mContact.show();
}

void		BabelMainWindow::timeoutOpenContact()
{
	cout << __FUNCTION__ << ": " << __DATE__ << endl;
	close();
	mContact.show();
}
