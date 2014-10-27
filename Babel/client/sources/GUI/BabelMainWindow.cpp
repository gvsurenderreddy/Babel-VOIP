#include <QFontDatabase>
#include "BabelMainWindow.hpp"

using namespace std;

BabelMainWindow::BabelMainWindow(void)
{
	mUi.setupUi(this);

	// Load and set font
	QFontDatabase	fontDb;
	QString	openSansLightPath = "fonts/OpenSans-Light.ttf";
	if (fontDb.addApplicationFont(openSansLightPath) != -1)
	{
		QFont	openSansLightFont = fontDb.font("Open Sans Light", "Normal", -1);
		mLogin.setFont(openSansLightFont);
		mSignup.setFont(openSansLightFont);
		mSetting.setFont(openSansLightFont);
	}

	// action when click on login/signin
	QObject::connect(mFlyer.getUi().login, SIGNAL(clicked()), &mLogin, SLOT(show()));
	QObject::connect(mFlyer.getUi().signup, SIGNAL(clicked()), &mSignup, SLOT(show()));
	QObject::connect(mFlyer.getUi().p, SIGNAL(clicked()), &mSetting, SLOT(show()));

	// action when click on back
	QObject::connect(mLogin.getUi().back, SIGNAL(clicked()), &mFlyer, SLOT(show()));
	QObject::connect(mSignup.getUi().back, SIGNAL(clicked()), &mFlyer, SLOT(show()));
	QObject::connect(mSetting.getUi().back, SIGNAL(clicked()), &mFlyer, SLOT(show()));
}

BabelMainWindow::~BabelMainWindow(void)
{
}

void	BabelMainWindow::show()
{
	/*
	Contact contact;

	contact.setAccountName("someAccountName");
	contact.setPassword("somePassword");
	emit askForAuthentication(contact);
	*/
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

void	BabelMainWindow::acceptContactSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::deleteContactSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::disconnectSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::sendMessageSuccess(const ErrorStatus &) {
}
