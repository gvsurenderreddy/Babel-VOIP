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

void	BabelMainWindow::updateContactList(const QList<Contact> &) {
}

void	BabelMainWindow::newContactInvitation(const Contact &) {
}

void	BabelMainWindow::newMessage(const Contact &, const QString &) {
}

void	BabelMainWindow::newCallInvitation(const Contact &) {
}

void	BabelMainWindow::startingCommunication(const Contact &, bool) {
}

void	BabelMainWindow::terminatingCommunication(const Contact &) {
}

void	BabelMainWindow::updateInfo(const Contact &) {
}

void	BabelMainWindow::createAccountSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::authenticateSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::sendInvitationSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::updateInfoSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::callContactSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::acceptCallSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::terminateCallSuccess(const ErrorStatus &) {
}
