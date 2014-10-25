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
