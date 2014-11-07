#include <QFontDatabase>
#include <QTextCodec>
#include <iostream>
#include <QMessageBox>
#include "BabelMainWindow.hpp"

using namespace std;

BabelMainWindow::BabelMainWindow(void)
	:	QMainWindow(), mCentralWidget(new QStackedWidget), mFlyer(new BabelFlyer),
		mSignup(new BabelInscription), mSetting(new BabelSetting), mMain(new BabelMain), mUpdate(new BabelUpdate)
{
	// Load and set font
	QFontDatabase	fontDb;
	QString	openSansLightPath = "fonts/OpenSans-Light.ttf";
	if (fontDb.addApplicationFont(openSansLightPath) != -1)
	{
		QFont	openSansLightFont = fontDb.font("Open Sans Light", "Normal", -1);
		mSignup->setFont(openSansLightFont);
		mSetting->setFont(openSansLightFont);
		mMain->setFont(openSansLightFont);
	}

	// set central widget
	setCentralWidget(mCentralWidget);
	mCentralWidget->addWidget(mMain);
	mCentralWidget->addWidget(mFlyer);
	mCentralWidget->addWidget(mUpdate);
	mCentralWidget->addWidget(mSignup);
	mCentralWidget->addWidget(mSetting);
	mMain->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	mFlyer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	mUpdate->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	mSignup->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	mSetting->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	QObject::connect(mSetting,	SIGNAL(exit()),											this, SLOT(displayFlyer()));
	QObject::connect(mSetting,	SIGNAL(askForConnection(const QString &, int)),			this, SLOT(connectionToServer(const QString &, int)));
	QObject::connect(mSignup,	SIGNAL(exit()),											this, SLOT(displayFlyer()));
	QObject::connect(mSignup,	SIGNAL(askForRegistration(const Contact &)),			this, SLOT(createAccount(const Contact &)));
	QObject::connect(mSignup,	SIGNAL(displayInformation(const QString &)),			this, SLOT(displayInformation(const QString &)));
	QObject::connect(mFlyer,	SIGNAL(displayRegistration()),							this, SLOT(displaySignUp()));
	QObject::connect(mFlyer,	SIGNAL(displaySettings()),								this, SLOT(displayOptions()));
	QObject::connect(mFlyer,	SIGNAL(askForAuthentication(const Contact &)),			this, SLOT(connexionToAccount(const Contact &)));
	QObject::connect(mUpdate,	SIGNAL(exit()),											this, SLOT(displayHome()));
	QObject::connect(mUpdate,	SIGNAL(updateContactInfo(Contact &)),					this, SLOT(updateContactInfo(Contact &)));
	QObject::connect(mMain,		SIGNAL(addContact(const Contact &)),					this, SLOT(addNewContact(const Contact &)));
	QObject::connect(mMain,		SIGNAL(deleteContact(const Contact &)),					this, SLOT(deleteContact(const Contact &)));
	QObject::connect(mMain,		SIGNAL(sendMessage(const Contact &, const QString &)),	this, SLOT(sendMessage(const Contact &, const QString &)));
	QObject::connect(mMain,		SIGNAL(callContact(const Contact &)),					this, SLOT(callContact(const Contact &)));
	QObject::connect(mMain,		SIGNAL(closeCall(const Contact &)),						this, SLOT(closeCall(const Contact &)));
	QObject::connect(mMain,		SIGNAL(logout()),										this, SLOT(disconnectionToAccount()));
	QObject::connect(mMain,		SIGNAL(updateContactInfo()),							this, SLOT(displayUpdate()));
}

BabelMainWindow::~BabelMainWindow(void) {}

void	BabelMainWindow::show() {
	updateContent(mFlyer);
	QMainWindow::show();
}

void	BabelMainWindow::updateContent(QWidget *widget) {
	if (mCentralWidget->currentWidget())
		mCentralWidget->currentWidget()->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	mCentralWidget->setCurrentWidget(widget);

	mCentralWidget->currentWidget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	widget->adjustSize();
	adjustSize();
}

void	BabelMainWindow::updateContactList(const QList<Contact> &list) {
	mMain->setContactList(list);
}

void	BabelMainWindow::newContactInvitation(const Contact &contact) {
	QMessageBox::StandardButton reply = QMessageBox::question(this, "Notification", contact.getAccountName() + " souhaite vous ajouter", QMessageBox::Yes | QMessageBox::No);
	emit askForAcceptingContact(contact, reply == QMessageBox::Yes);
}

void	BabelMainWindow::newMessage(const Contact &contact, const QString &msg) {
	mMain->receiveMessage(contact, msg);
}

void	BabelMainWindow::newCallInvitation(const Contact &contact) {
	QMessageBox::StandardButton reply = QMessageBox::question(this, "Notification", contact.getAccountName() + " vous invite à appeler", QMessageBox::Yes | QMessageBox::No);
	emit askForAcceptingCall(contact, reply == QMessageBox::Yes);
}

void	BabelMainWindow::startingCommunication(const Contact &contact, bool hasAccepted) {
	mMain->startCommunication(contact, hasAccepted);
}

void	BabelMainWindow::terminatingCommunication(const Contact &contact) {
	mMain->terminateCommunication(contact);
}

void	BabelMainWindow::updateInfo(const Contact &contact) {
	mContact = contact;
	mMain->setUser(mContact);
}

void	BabelMainWindow::createAccountSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred()) {
		updateContent(mFlyer);
		displayInformation("Votre compte a été crée avec succès.");
	}
	else
		displayInformation("Votre compte n'a pas pu être créé.");
}

void	BabelMainWindow::authenticateSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
		updateContent(mMain);
	else
		displayInformation("Problème de connection!\nVeuillez vérifier votre nom de compte et votre mot de passe.");
}

void	BabelMainWindow::sendInvitationSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
		displayInformation("Demande d'invitation échoué :(");
}

void	BabelMainWindow::updateInfoSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
		displayInformation("Le profil n'a pas pu être mis à jour.");
	else
		displayInformation("Le profil a été mis à jour");
}

void	BabelMainWindow::callContactSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
		displayInformation("L'appel a échoué.");
}

void	BabelMainWindow::acceptCallSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
		displayInformation("L'appel a échoué.");
}

void	BabelMainWindow::terminateCallSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
		displayInformation("Une erreur s'est produit au moment de stopper l'appel.");
}

void	BabelMainWindow::acceptContactSuccess(const ErrorStatus &) {
}

void	BabelMainWindow::deleteContactSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
		displayInformation("Le contact a bien été supprimé :p");
	else
		displayInformation("Le contact n'a pas pu être supprimé :/");
}

void	BabelMainWindow::disconnectSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		updateContent(mFlyer);
		displayInformation("Vous venez de vous déconnecter ;)");
	}
	else
		displayInformation("Erreur à la déconnexion :s");
}

void	BabelMainWindow::sendMessageSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
		displayInformation("Impossible d'envoyer le message au destinataire :(");
}

void	BabelMainWindow::connectToServerSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred()) {
		displayInformation("Connecté au serveur");
		updateContent(mFlyer);
	}
	else
		displayInformation("Echec de la connection au serveur.");
}

void	BabelMainWindow::disconnectedFromServer(void) {
	updateContent(mFlyer);
	displayInformation("Vous êtes connecté à aucun serveur :/");
}

void	BabelMainWindow::connectionToServer(const QString &host, int port)
{
	emit askForConnectionToServer(host, port);
}

void	BabelMainWindow::createAccount(const Contact &contact) {
	emit askForRegistration(contact);
}

void		BabelMainWindow::connexionToAccount(const Contact &contact) {
	mContact = contact;
	emit askForAuthentication(contact);
}

void		BabelMainWindow::addNewContact(const Contact &contact) {
	emit askForAddingContact(contact);
}

void		BabelMainWindow::sendMessage(const Contact &contact, const QString &message) {
	emit askForSendingMessage(contact, message);
}

void		BabelMainWindow::callContact(const Contact &contact)
{
		emit askForCalling(contact);
}

void	BabelMainWindow::closeCall(const Contact &contact) {
	emit askForTerminatingCall(contact);
}

void		BabelMainWindow::disconnectionToAccount()
{
	emit askForDisconnection();
	updateContent(mFlyer);
}

void	BabelMainWindow::displayOptions(void) {
	updateContent(mSetting);
}

void	BabelMainWindow::displaySignUp(void) {
	updateContent(mSignup);
}

void	BabelMainWindow::displayFlyer(void) {
	updateContent(mFlyer);
}

void	BabelMainWindow::deleteContact(const Contact &contact) {
	emit askForDeletingContact(contact);
}

void	BabelMainWindow::displayHome(void) {
	updateContent(mMain);
}

void	BabelMainWindow::displayUpdate(void) {
	updateContent(mUpdate);
}

void	BabelMainWindow::updateContactInfo(Contact &contact) {
	contact.setAccountName(mContact.getAccountName());

	emit askForUpdatingInfo(contact);
}

void	BabelMainWindow::displayInformation(const QString &message) {
	mDialog.setMessage(message);
	mDialog.show();
}