#include <iostream>
#include "BabelMainWindow.hpp"

using namespace std;

BabelMainWindow::BabelMainWindow(void)
{
	mUi.setupUi(this);

	// action when click on login
	QObject::connect(mFlyer.getUi().login, SIGNAL(clicked()), &mConnexion, SLOT(show()));
	QObject::connect(mFlyer.getUi().login, SIGNAL(clicked()), &mFlyer, SLOT(hide()));

	// action when click on back
	QObject::connect(mConnexion.getUi().back, SIGNAL(clicked()), &mFlyer, SLOT(show()));
}

BabelMainWindow::~BabelMainWindow(void)
{
	cout << __FUNCTION__ << endl;
}

void	BabelMainWindow::show()
{
	mFlyer.show();
}
