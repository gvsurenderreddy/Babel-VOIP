#include <QFontDatabase>
#include <QTextCodec>
#include <iostream>
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
		mMain.setFont(openSansLightFont);
	}

	// action when click on login/signin
	QObject::connect(mFlyer.getUi().signup, SIGNAL(clicked()), &mSignup, SLOT(show()));
	QObject::connect(mFlyer.getUi().p, SIGNAL(clicked()), &mSetting, SLOT(show()));

	// action when click on back
	QObject::connect(mLogin.getUi().back, SIGNAL(clicked()), &mFlyer, SLOT(show()));
	QObject::connect(mSignup.getUi().back, SIGNAL(clicked()), &mFlyer, SLOT(show()));
	QObject::connect(mSetting.getUi().back, SIGNAL(clicked()), &mFlyer, SLOT(show()));

	// setting: when clicked "se connecter"
	QObject::connect(mSetting.getUi().connexion, SIGNAL(clicked()), 
		this, SLOT(connectionToServer()));

	// inscription: when clicked "valider"
	QObject::connect(mSignup.getUi().ok, SIGNAL(clicked()), 
		this, SLOT(createAccount()));

	// connexion: when connect to account
	QObject::connect(mFlyer.getUi().login, SIGNAL(clicked()), this, SLOT(connexionToAccount()));

	// debug
	QObject::connect(mFlyer.getUi().login, SIGNAL(clicked()), &mMain, SLOT(show()));
}

BabelMainWindow::~BabelMainWindow(void)
{
}

void	BabelMainWindow::show()
{
	//Contact contact;

    // login
	/*
	contact.setAccountName("navid");
	contact.setPassword("123456789");
	emit askForAuthentication(contact);
	*/


    // registration
    /*
    contact.setAccountName("navid");
    contact.setPassword("123456789");
    contact.setPseudo("desten");
    emit askForRegistration(contact);
    */

	mFlyer.show();
}

void	BabelMainWindow::updateContactList(const QList<Contact> &list) {
	mMain.getModel()->setContactList(list);
}

void	BabelMainWindow::newContactInvitation(const Contact &contact) {
	// A completer
	mMain.getModel()->getContactList() << contact;
	mMain.getModel()->sort();
	mMain.getUi().listContactView->setModel(mMain.getModel());

	mDialog.setMessage(contact.getAccountName() + " figure désormais dans vos contacts \\o/");
	mDialog.show();
	//
}

void	BabelMainWindow::newMessage(const Contact &contact, const QString &msg) {
	mDialog.setMessage(contact.getAccountName() + "vous envoie:\n" + msg);
	mDialog.show();
}

void	BabelMainWindow::newCallInvitation(const Contact &) {
}

void	BabelMainWindow::startingCommunication(const Contact &, bool) {
}

void	BabelMainWindow::terminatingCommunication(const Contact &) {
}

void	BabelMainWindow::updateInfo(const Contact &contact) {
	mContact = contact;
	// debug
	QString	debug("");

	debug += contact.getAccountName() + "\n";
	mDialog.setMessage(debug);
	mDialog.show();
	//
}

void	BabelMainWindow::createAccountSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mDialog.setWindowTitle("Félicitation");
		mDialog.setMessage("Votre compte a été crée avec succès :D");
	}
	else
	{
		mDialog.setWindowTitle("Erreur à la création :(");
		mDialog.setMessage("Votre compte n'a pas pu se créer :(\n\nError code: " + QString::number(es.getErrorCode()));
	}
	mDialog.show();
}

void	BabelMainWindow::authenticateSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mFlyer.hide();
		mMain.show();
		mMain.getUi().name->setText(mFlyer.getEmail());
	}
	else
	{
		mDialog.setWindowTitle("Erreur de connexion :(");
		mDialog.setMessage("Problème de connexion\nVeuillez vérifier vos email ou mot de passe ;)");
	}
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

void	BabelMainWindow::connectToServerSuccess(const ErrorStatus &es) {
	QString	success = !es.errorOccurred() ? "Succès" : "Echec";

	mDialog.setMessage(success + " à la connection de l'addresse IP (" + mSetting.getHost() + ")");
	mDialog.show();
}

void	BabelMainWindow::disconnectedFromServer(void) {
	mDialog.setMessage("Vous êtes connecté à aucun serveur :/");
}

void	BabelMainWindow::connectionToServer()
{
	emit askForConnectionToServer(mSetting.getHost(), mSetting.getPort());
}

void	BabelMainWindow::createAccount()
{
	Contact contact;
	
	if (mSignup.getIsRegister())
	{
		// set Contacts
		contact.setAccountName(mSignup.getEmail());
		contact.setPseudo(mSignup.getPseudo());
		contact.setPassword(mSignup.getPwd());

		mSignup.setIsRegister(false);
		emit askForRegistration(contact);
	}
	else
	{
		mDialog.setMessage("Erreur à l'inscription.\nVeuillez vérifier les saisies de vos mot de passe.");
	}
	mDialog.show();
}

void		BabelMainWindow::connexionToAccount()
{
	Contact	contact;

	contact.setAccountName(mFlyer.getEmail());
	contact.setPassword(mFlyer.getPwd());
	emit askForAuthentication(contact);
	mDialog.show();
}