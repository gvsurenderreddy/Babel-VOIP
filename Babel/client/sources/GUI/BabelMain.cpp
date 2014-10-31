#include "BabelMain.hpp"

BabelMain::BabelMain()
	: QWidget(), mNewContact("")
{
	mUi.setupUi(this);
	mModel = new ContactListModel(this);

	// debug test contact
	Contact	contact;
	Contact contact1;
	Contact contact2;
	Contact contact3;
	contact.setAccountName("jean.jacque@gmail.com");
	contact.setPseudo("jeanjacquedu75016");
	contact1.setAccountName("michudupont@gmail.com");
	contact1.setPseudo("michu");
	contact2.setAccountName("bernard.delafontaine@gmail.com");
	contact2.setPseudo("bernardbgdu93");
	contact3.setAccountName("lourde@gmail.com");
	contact3.setPseudo("lourde93delateci");
	mModel->getContactList() << contact << contact1 << contact2 << contact3;
	mModel->sort();
	mUi.listContactView->setModel(mModel);
	//

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	QObject::connect(mUi.listContactView, SIGNAL(clicked(QModelIndex const &)), this, SLOT(onClickContact(QModelIndex const &)));
	QObject::connect(mUi.addContact, SIGNAL(clicked()), this, SLOT(onClickAddContact()));
}

BabelMain::~BabelMain()
{
	delete mModel;
}

void		BabelMain::onClickContact(QModelIndex const &index)
{
	mUi.name->setText(mModel->getContactList()[index.row()].getPseudo());
}

void		BabelMain::onClickAddContact()
{
	
}