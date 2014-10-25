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

void	BabelMainWindow::updateContactList(const QList<Contact> &contacts) {
}

void	BabelMainWindow::newContactInvitation(const Contact &contact) {
}

void	BabelMainWindow::newMessage(const Contact &contact, const QString &message) {
}

void	BabelMainWindow::newCallInvitation(const Contact &contact) {
}

void	BabelMainWindow::startingCommunication(const Contact &contact, bool hasAccepted) {
}

void	BabelMainWindow::terminatingCommunication(const Contact &contact) {
}

void	BabelMainWindow::updateInfo(const Contact &contact) {
}

void	BabelMainWindow::createAccountSuccess(const ErrorStatus &errorStatus) {
}

void	BabelMainWindow::authenticateSuccess(const ErrorStatus &errorStatus) {
}

void	BabelMainWindow::sendInvitationSuccess(const ErrorStatus &errorStatus) {
}

void	BabelMainWindow::updateInfoSuccess(const ErrorStatus &errorStatus) {
}

void	BabelMainWindow::callContactSuccess(const ErrorStatus &errorStatus) {
}

void	BabelMainWindow::acceptCallSuccess(const ErrorStatus &errorStatus) {
}

void	BabelMainWindow::terminateCallSuccess(const ErrorStatus &errorStatus) {
}
