#include <QFontDatabase>
#include <QTextCodec>
#include <iostream>
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
	mCentralWidget->addWidget(mFlyer);
	mCentralWidget->addWidget(mSignup);
	mCentralWidget->addWidget(mSetting);
	mCentralWidget->addWidget(mMain);
	mCentralWidget->addWidget(mUpdate);
	mFlyer->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	mSignup->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	mSetting->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	mMain->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	mUpdate->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	// action when click on login/signin
	QObject::connect(mFlyer->getUi().signup, SIGNAL(clicked()), this, SLOT(displaySignUp()));
	QObject::connect(mFlyer->getUi().p, SIGNAL(clicked()), this, SLOT(displayOptions()));

	// action when click on back
	QObject::connect(mSignup->getUi().back, SIGNAL(clicked()), this, SLOT(displayFlyer()));
	QObject::connect(mSetting->getUi().back, SIGNAL(clicked()), this, SLOT(displayFlyer()));

	// setting: when clicked "se connecter"
	QObject::connect(mSetting->getUi().connexion, SIGNAL(clicked()), 
		this, SLOT(connectionToServer()));

	// inscription: when clicked "valider"
	QObject::connect(mSignup->getUi().ok, SIGNAL(clicked()), 
		this, SLOT(createAccount()));

	// connexion: when connect to account
	QObject::connect(mFlyer->getUi().login, SIGNAL(clicked()), this, SLOT(connexionToAccount()));

	// connexion: when add contact
	QObject::connect(mMain->getUi().addContact, SIGNAL(clicked()), this, SLOT(addNewContact()));

	// when deleting contact
	QObject::connect(mMain->getUi().deleteContact, SIGNAL(clicked()), this, SLOT(deleteContact()));

	// when send message to somebody
	QObject::connect(mMain->getUi().send, SIGNAL(clicked()), this, SLOT(sendMessage()));


	// when call somebody
	QObject::connect(mMain->getUi().call, SIGNAL(clicked()), this, SLOT(callContact()));

	// when deconnection
	QObject::connect(mMain->getUi().logout, SIGNAL(clicked()), this, SLOT(disconnectionToAccount()));

	// update window
	QObject::connect(mMain, SIGNAL(updateContactInfo()), this, SLOT(displayUpdate()));
	QObject::connect(mUpdate, SIGNAL(exit()), this, SLOT(displayHome()));
	QObject::connect(mUpdate, SIGNAL(updateContactInfo(Contact &)), this, SLOT(updateContactInfo(Contact &)));

	// trigger return pressed
	QObject::connect(mFlyer->getUi().emailEdit, SIGNAL(returnPressed()), mFlyer->getUi().login, SIGNAL(clicked()));
	QObject::connect(mFlyer->getUi().pwdEdit, SIGNAL(returnPressed()), mFlyer->getUi().login, SIGNAL(clicked()));

	QObject::connect(mSetting->getUi().addrEdit, SIGNAL(returnPressed()), mSetting->getUi().connexion, SIGNAL(clicked()));
	QObject::connect(mSetting->getUi().portEdit, SIGNAL(returnPressed()), mSetting->getUi().connexion, SIGNAL(clicked()));

	QObject::connect(mSignup->getUi().emailEdit, SIGNAL(returnPressed()), mSignup->getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSignup->getUi().pseudoEdit, SIGNAL(returnPressed()), mSignup->getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSignup->getUi().pwdEdit1, SIGNAL(returnPressed()), mSignup->getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSignup->getUi().pwdEdit2, SIGNAL(returnPressed()), mSignup->getUi().ok, SIGNAL(clicked()));

	QObject::connect(mMain->getUi().newContact, SIGNAL(returnPressed()), mMain->getUi().addContact, SIGNAL(clicked()));
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
	mMain->getModel()->setContactList(list);
}

void	BabelMainWindow::newContactInvitation(const Contact &contact) {
	emit askForAcceptingContact(contact, true);
}

void	BabelMainWindow::newMessage(const Contact &contact, const QString &msg) {
	MessageListModel::sMessage	message = {
		contact.getAccountName(),
		msg,
		QDateTime::currentDateTime()
	};

	// set current contact's list message on model
	mMain->getCurrentContact().getMessages() << message;
	mMain->getMessages()->setMessageList(mMain->getCurrentContact().getMessages());

	//mMain->getMessages()->getMessageList() << message;
	emit mMain->getMessages()->layoutChanged();
}

void	BabelMainWindow::newCallInvitation(const Contact &contact) {
	emit askForAcceptingCall(contact, true);
}

void	BabelMainWindow::startingCommunication(const Contact &contact, bool hasAccepted) {
	if (hasAccepted)
	{
		mMain->getUi().call->setText("Raccrocher");
		mDialog.setMessage(contact.getAccountName() + " a accepté votre appel :)");
		mMain->setContactInCall(contact);
		mMain->setIsCall(true);
	}
	else
		mDialog.setMessage(contact.getAccountName() + " a refusé votre appel :(");
	mDialog.show();
}

void	BabelMainWindow::terminatingCommunication(const Contact &contact) {
	mMain->getUi().call->setText("Appeler");
	mDialog.setMessage(contact.getAccountName() + " a quitté l'appel...");
	mMain->setIsCall(false);
}

void	BabelMainWindow::updateInfo(const Contact &contact) {
	mContact = contact;
}

void	BabelMainWindow::createAccountSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		updateContent(mFlyer);
		mFlyer->getUi().emailEdit->setText(mSignup->getEmail());
		mDialog.setMessage("Votre compte a été crée avec succès :D");
	}
	else
	{
		mDialog.setMessage("Votre compte n'a pas pu se créer :(\n\nError code: " + QString::number(es.getErrorCode()));
	}
	mDialog.show();
}

void	BabelMainWindow::authenticateSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mDialog.hide();
		updateContent(mMain);
		mMain->getUi().name->setText(mFlyer->getEmail());
	}
	else
	{
		mDialog.setWindowTitle("Erreur de connexion :(");
		mDialog.setMessage("Problème de connexion\nVeuillez vérifier vos email ou mot de passe ;)");
		mDialog.show();
	}
}

void	BabelMainWindow::sendInvitationSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
	{
		mDialog.setMessage("Demande d'invitation échoué :(");
		mDialog.show();
	}
}

void	BabelMainWindow::updateInfoSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
		mDialog.setMessage("Le profil n'a pas pu être mis à jour.");
	else
		mDialog.setMessage("Le profil a été mis à jour");

	mDialog.show();
}

void	BabelMainWindow::callContactSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mMain->setIsCall(true);
	}
	else
	{
		mDialog.setMessage("L'appel a échoué :/");
		mDialog.show();
		mMain->setIsCall(false);
	}
}

void	BabelMainWindow::acceptCallSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mMain->setIsCall(true);
	}
	else
	{
		mDialog.setMessage("Votre appel n'a pas pu être établit... :/");
		mDialog.show();
	}
}

void	BabelMainWindow::terminateCallSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
	{
		mDialog.setMessage("Une erreur s'est produit au moment de stopper l'appel...");
		mDialog.show();
	}
	mMain->setIsCall(false);
}

void	BabelMainWindow::acceptContactSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
		mDialog.setMessage("Vous avez un nouveau contact ! :)");
	else
		mDialog.setMessage("Le contact n'existe pas... :(");
	mDialog.show();
}

void	BabelMainWindow::deleteContactSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mDialog.setMessage("Le contact a bien été supprimé :p");
	}
	else
	{
		mDialog.setMessage("Le contact n'a pas pu être supprimé :/");
	}
	mDialog.show();
}

void	BabelMainWindow::disconnectSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		updateContent(mFlyer);
		mMain->getDialog().hide();
		mDialog.setMessage("Vous venez de vous déconnecter ;)");
	}
	else
		mDialog.setMessage("Erreur à la déconnexion :s");
	mDialog.show();
}

void	BabelMainWindow::sendMessageSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
	{
		/*
		mDialog.setMessage("Impossible d'envoyer le message au destinataire :(");
		mDialog.show();
		*/
	}
}

void	BabelMainWindow::connectToServerSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mDialog.setMessage("Succès à la connection de l'addresse IP (" + mSetting->getHost() + ")");
		updateContent(mFlyer);
	}
	else
	{
		mDialog.setMessage("Echec à la connection de l'addresse IP (" + mSetting->getHost() + ")");
	}
	mDialog.show();
}

void	BabelMainWindow::disconnectedFromServer(void) {
	updateContent(mFlyer);
	mDialog.setMessage("Vous êtes connecté à aucun serveur :/");
	mDialog.show();
}

void	BabelMainWindow::connectionToServer()
{
	emit askForConnectionToServer(mSetting->getHost(), mSetting->getPort());
}

void	BabelMainWindow::createAccount()
{
	Contact contact;
	
	if (mSignup->getIsRegister())
	{
		// set Contacts
		contact.setAccountName(mSignup->getEmail());
		contact.setPseudo(mSignup->getPseudo());
		contact.setPassword(mSignup->getPwd());

		mSignup->setIsRegister(false);
		emit askForRegistration(contact);
	}
	else
	{
		mDialog.setMessage("Erreur à l'inscription.\nVeuillez vérifier les saisies de vos mot de passe ;)");
		mDialog.show();
	}
}

void		BabelMainWindow::connexionToAccount()
{
	Contact	contact;

	contact.setAccountName(mFlyer->getEmail());
	contact.setPassword(mFlyer->getPwd());
	emit askForAuthentication(contact);
}

void		BabelMainWindow::addNewContact()
{
	Contact	contact;

	contact.setAccountName(mMain->getUi().newContact->text());
	emit askForAddingContact(contact);
}

void		BabelMainWindow::sendMessage()
{
	if (mMain->getUi().messageEdit->toPlainText() != "")
	{
		MessageListModel::sMessage	msg = {
			mContact.getPseudo(),
			mMain->getUi().messageEdit->toPlainText(),
			QDateTime::currentDateTime()
		};

		// set your list message on model
		mMain->getCurrentContact().getMessages() << msg;
		mMain->getMessages()->setMessageList(mMain->getCurrentContact().getMessages());

		//mMain->getMessages()->getMessageList() << msg;
		emit mMain->getMessages()->layoutChanged();

		emit askForSendingMessage(mMain->getCurrentContact(), msg.msg);
		mMain->getUi().messageEdit->clear();
	}
	mMain->getUi().messageEdit->setFocus();
}

void		BabelMainWindow::callContact()
{
	if (mMain->getUi().call->text() == "Appeler")
		emit askForCalling(mMain->getCurrentContact());
	else
		emit askForTerminatingCall(mMain->getContactInCall());
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

void	BabelMainWindow::deleteContact(void) {
	emit askForDeletingContact(mMain->getCurrentContact());
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
