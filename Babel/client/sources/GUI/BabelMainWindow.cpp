#include <QFontDatabase>
#include <QTextCodec>
#include <iostream>
#include "BabelMainWindow.hpp"

using namespace std;

BabelMainWindow::BabelMainWindow(void)
	: QMainWindow()
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
	//QObject::connect(mFlyer.getUi().login, SIGNAL(clicked()), &mMain, SLOT(show()));

	// connexion: when add contact
	QObject::connect(mMain.getUi().addContact, SIGNAL(clicked()), this, SLOT(addNewContact()));

	// when send message to somebody
	QObject::connect(mMain.getUi().send, SIGNAL(clicked()), this, SLOT(sendMessage()));


	// when close flyer
	QObject::connect(mFlyer.getUi().close, SIGNAL(clicked()), &mDialog, SLOT(close()));

	// when call somebody
	QObject::connect(mMain.getUi().call, SIGNAL(clicked()), this, SLOT(callContact()));

	// trigger return pressed
	QObject::connect(mFlyer.getUi().emailEdit, SIGNAL(returnPressed()), mFlyer.getUi().login, SIGNAL(clicked()));
	QObject::connect(mFlyer.getUi().pwdEdit, SIGNAL(returnPressed()), mFlyer.getUi().login, SIGNAL(clicked()));

	QObject::connect(mSetting.getUi().addrEdit, SIGNAL(returnPressed()), mSetting.getUi().connexion, SIGNAL(clicked()));
	QObject::connect(mSetting.getUi().portEdit, SIGNAL(returnPressed()), mSetting.getUi().connexion, SIGNAL(clicked()));

	QObject::connect(mSetting.getUi().pseudoEdit, SIGNAL(returnPressed()), mSetting.getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSetting.getUi().pwdEdit1, SIGNAL(returnPressed()), mSetting.getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSetting.getUi().pwdEdit2, SIGNAL(returnPressed()), mSetting.getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSetting.getUi().pwdEdit3, SIGNAL(returnPressed()), mSetting.getUi().ok, SIGNAL(clicked()));

	QObject::connect(mSignup.getUi().emailEdit, SIGNAL(returnPressed()), mSignup.getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSignup.getUi().pseudoEdit, SIGNAL(returnPressed()), mSignup.getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSignup.getUi().pwdEdit1, SIGNAL(returnPressed()), mSignup.getUi().ok, SIGNAL(clicked()));
	QObject::connect(mSignup.getUi().pwdEdit2, SIGNAL(returnPressed()), mSignup.getUi().ok, SIGNAL(clicked()));

	QObject::connect(mMain.getUi().newContact, SIGNAL(returnPressed()), mMain.getUi().addContact, SIGNAL(clicked()));
}

BabelMainWindow::~BabelMainWindow(void)
{
}

void	BabelMainWindow::show()
{
	mFlyer.show();
}

void	BabelMainWindow::updateContactList(const QList<Contact> &list) {
	mMain.getModel()->setContactList(list);
}

void	BabelMainWindow::newContactInvitation(const Contact &contact) {
	// A CHANGER
	emit askForAcceptingContact(contact, true);
}

void	BabelMainWindow::newMessage(const Contact &contact, const QString &msg) {
	MessageListModel::sMessage	message = {
		contact.getAccountName(),
		msg,
		QDateTime::currentDateTime()
	};
	mMain.getMessages()->getContactList() << message;
	mMain.getUi().listView->setModel(mMain.getMessages());
}

void	BabelMainWindow::newCallInvitation(const Contact &contact) {
	// A CHANGER
	emit askForAcceptingCall(contact, true);
}

void	BabelMainWindow::startingCommunication(const Contact &contact, bool hasAccepted) {
	if (hasAccepted)
		mDialog.setMessage(contact.getAccountName() + " a accepté votre appel :)");
	else
		mDialog.setMessage(contact.getAccountName() + " a refusé votre appel :(");
	mDialog.show();
}

void	BabelMainWindow::terminatingCommunication(const Contact &contact) {
	mDialog.setMessage(contact.getAccountName() + " a quitté l'appel...");
}

void	BabelMainWindow::updateInfo(const Contact &contact) {
	mContact = contact;
}

void	BabelMainWindow::createAccountSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mSignup.hide();
		mFlyer.show();
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
		mFlyer.hide();
		mMain.show();
		mMain.getUi().name->setText(mFlyer.getEmail());
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
	{
		mDialog.setMessage("Votre profile est introuvable - -'");
		mDialog.show();
	}
}

void	BabelMainWindow::callContactSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
	{
		mDialog.setMessage("L'appel a échoué :/");
		mDialog.show();
	}
}

void	BabelMainWindow::acceptCallSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
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
		mDialog.show();
	}
	else
	{
		mDialog.setMessage("Le contact n'a pas pu être supprimé :/");
		mDialog.show();
	}
}

void	BabelMainWindow::disconnectSuccess(const ErrorStatus &es) {
	if (!es.errorOccurred())
	{
		mMain.hide();
		mFlyer.show();
		mDialog.setMessage("Vous venez de vous déconnecter ;)");
	}
	else
		mDialog.setMessage("Erreur à la déconnexion :s");
	mDialog.show();
}

void	BabelMainWindow::sendMessageSuccess(const ErrorStatus &es) {
	if (es.errorOccurred())
	{
		mDialog.setMessage("Impossible d'envoyer le message au destinataire :/");
		mDialog.show();
	}
}

void	BabelMainWindow::connectToServerSuccess(const ErrorStatus &es) {
	QString	success = !es.errorOccurred() ? "Succès" : "Echec";

	mDialog.setMessage(success + " à la connection de l'addresse IP (" + mSetting.getHost() + ")");
	mDialog.show();
}

void	BabelMainWindow::disconnectedFromServer(void) {
	mMain.hide();
	mMain.getDialog().hide();
	mFlyer.show();
	mDialog.setMessage("Vous êtes connecté à aucun serveur :/");
	mDialog.show();
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
		mDialog.setMessage("Erreur à l'inscription.\nVeuillez vérifier les saisies de vos mot de passe ;)");
		mDialog.show();
	}
}

void		BabelMainWindow::connexionToAccount()
{
	Contact	contact;

	contact.setAccountName(mFlyer.getEmail());
	contact.setPassword(mFlyer.getPwd());
	emit askForAuthentication(contact);
}

void		BabelMainWindow::addNewContact()
{
	Contact	contact;

	contact.setAccountName(mMain.getUi().newContact->text());
	emit askForAddingContact(contact);
}

void		BabelMainWindow::sendMessage()
{
	if (mMain.getUi().messageEdit->toPlainText() != "")
	{
		emit askForSendingMessage(mMain.getCurrentContact(), mMain.getUi().messageEdit->toPlainText());

		// debug
		MessageListModel::sMessage	msg = {
			mContact.getPseudo(),
			mMain.getUi().messageEdit->toPlainText(),
			QDateTime::currentDateTime()
		};
		mMain.getMessages()->getContactList() << msg;
		mMain.getUi().listView->setModel(mMain.getMessages());
		//

		mDialog.setMessage(mMain.getUi().messageEdit->toPlainText());
		mDialog.show();
		// end
	}
}

void		BabelMainWindow::callContact()
{
	emit askForCalling(mMain.getCurrentContact());
}