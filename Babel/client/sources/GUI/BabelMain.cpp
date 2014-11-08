#include <QFontDatabase>
#include "BabelMain.hpp"

BabelMain::BabelMain()
	: QWidget(), mIsCall(false)
{
	mUi.setupUi(this);

	mModel = new ContactListModel(this);
	mMessages = new MessageListModel(this);
	mUi.listContactView->setModel(mModel);
	mUi.listView->setModel(mMessages);

	mOriginalSize = size();

    // Load and set font
    this->setWindowTitle("Studio Babel :: Main");
    QFontDatabase	fontDb;
    QString	openSansLightPath = "fonts/OpenSans-Light.ttf";
    if (fontDb.addApplicationFont(openSansLightPath) != -1)
    {
        QFont	openSansLightFont = fontDb.font("Open Sans Light", "Normal", -1);
        this->setFont(openSansLightFont);
    }

	QObject::connect(mUi.listContactView, SIGNAL(clicked(QModelIndex const &)), this, SLOT(onClickContact(QModelIndex const &)));
	QObject::connect(mUi.newContact, SIGNAL(returnPressed()), this, SLOT(onAddContactButtonClicked()));
	QObject::connect(mUi.addContact, SIGNAL(clicked()), this, SLOT(onAddContactButtonClicked()));
	QObject::connect(mUi.options, SIGNAL(clicked()), this, SLOT(onOptionsButtonClicked()));
	QObject::connect(mUi.deleteContact, SIGNAL(clicked()), this, SLOT(onDeleteContactButtonClicked()));
	QObject::connect(mUi.send, SIGNAL(clicked()), this, SLOT(onSendButtonClicked()));
	QObject::connect(mUi.call, SIGNAL(clicked()), this, SLOT(onCallButtonClicked()));
	QObject::connect(mUi.logout, SIGNAL(clicked()), this, SLOT(onLogoutButtonClicked()));
}

BabelMain::~BabelMain(void)
{
	delete mModel;
	delete mMessages;
}

void	BabelMain::paintEvent(QPaintEvent *) {
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QSize	BabelMain::minimumSizeHint() const {
	return mOriginalSize;
}

void	BabelMain::setContactList(const QList<Contact> &contacts) {
	mModel->setContactList(contacts);
}

void		BabelMain::onClickContact(QModelIndex const &index)
{
	mCurrentContact = mModel->getContactList()[index.row()];

    mUi.accountName->setText(mCurrentContact.getAccountName());
    mUi.pseudo->setText(mCurrentContact.getPseudo());

    static const struct DisplayStatus {
    	Contact::Status status;
    	QString 		text;
    } displayStatus[] = {
    	{ Contact::CONNECTED, 		"Connecté" 			},
    	{ Contact::DISCONNECTED, 	"Déconnecté" 		},
    	{ Contact::BUSY, 			"Occupé" 			},
    	{ Contact::AWAY, 			"Absent" 			},
    	{ Contact::KIPOUR, 			"Kipour" 			},
    	{ Contact::SLEEPING, 		"Grasse mat' 10h" 	},
    	{ Contact::RAMADAN, 		"Ramadan" 			},
    	{ Contact::SPORT, 			"Sport" 			},
    	{ Contact::TOILET, 			"Petit coin" 		},
    	{ Contact::YOLO, 			"Yolo" 				},
    	{ Contact::CRYING, 			"Parti bouder" 		},
    	{ Contact::UNKNOWN, 		"" 					}
    };

    for (int i = 0; displayStatus[i].status != Contact::UNKNOWN; i++)
	    if (mCurrentContact.getStatus() == displayStatus[i].status) {
    	    mUi.status->setText(displayStatus[i].text);
    	    break;
	    }
   
    mMessages->setMessageList(mCurrentContact.getMessages());
}

void	BabelMain::onOptionsButtonClicked(void) {
	emit updateContactInfo();
}

void	BabelMain::onAddContactButtonClicked(void) {
	Contact	contact;

	contact.setAccountName(mUi.newContact->text());

    if (mUi.newContact->text().length())
	    emit addContact(contact);
}

void	BabelMain::onDeleteContactButtonClicked(void) {
	emit deleteContact(mCurrentContact);
}

void	BabelMain::setUser(const Contact &contact) {
	mUser = contact;
    this->setWindowTitle("Studio Babel :: Main (account: '" + mUser.getPseudo() + "'");
}

void	BabelMain::onSendButtonClicked(void) {
	QString message = mUi.messageEdit->toPlainText();

	if (message != "") {
		Contact::Message msg = { mUser.getPseudo(), message, QDateTime::currentDateTime() };

		QList<Contact> &contacts = mModel->getContactList();
		for (int i = 0; i < contacts.count(); i++)
			if (contacts[i].getAccountName() == mCurrentContact.getAccountName()) {
				contacts[i].getMessages() << msg;
				mCurrentContact = contacts[i];
				mMessages->setMessageList(mCurrentContact.getMessages());

				emit sendMessage(mCurrentContact, msg.msg);
			}
	}

	mUi.messageEdit->setFocus();
	mUi.messageEdit->clear();
}

void	BabelMain::onCallButtonClicked(void) {
	if (mIsCall)
		emit closeCall(mContactInCall);
	else
		emit callContact(mCurrentContact);
}

void	BabelMain::onLogoutButtonClicked(void) {
	emit logout();
}

void	BabelMain::receiveMessage(const Contact &contact, const QString &msg) {
	Contact::Message message = { contact.getAccountName(), msg, QDateTime::currentDateTime() };

	QList<Contact> &contacts = mModel->getContactList();
	for (int i = 0; i < contacts.count(); i++)
		if (contacts[i].getAccountName() == contact.getAccountName()) {
			contacts[i].getMessages() << message;

			if (contact.getAccountName() == mCurrentContact.getAccountName()) {
				mCurrentContact = contacts[i];
				mMessages->setMessageList(mCurrentContact.getMessages());
			}
		}
}

void	BabelMain::startCommunication(const Contact &contact, bool hasAccepted) {
	if (hasAccepted) {
		mUi.call->setText("Raccrocher");
		mContactInCall = contact;
		mIsCall = true;

		emit displayInformation(contact.getAccountName() + " a accepté votre appel.");
	}
	else
		emit displayInformation(contact.getAccountName() + " a refusé votre appel.");
}

void	BabelMain::terminateCommunication(const Contact &) {
	mUi.call->setText("Appeler");
	mIsCall = false;

	emit displayInformation("Appel terminé");
}
