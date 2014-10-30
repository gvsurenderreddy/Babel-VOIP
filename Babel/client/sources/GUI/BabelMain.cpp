#include "BabelMain.hpp"

BabelMain::BabelMain()
	: QWidget()
{
	mUi.setupUi(this);
	mModel = new ContactListModel(this);

	Contact	contact;

	contact.setAccountName("jean.jacque@gmail.com");
	contact.setPseudo("jeanbgdu75016");
	mModel->getContactList().push_back(contact);

	// Remove window borders
	setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

	// Desable resize window
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

	QObject::connect(mUi.listContactView, SIGNAL(clicked(QModelIndex const &)), this, SLOT(onClickContact(QModelIndex const &)));
}

BabelMain::~BabelMain()
{
	delete mModel;
}

void		BabelMain::onClickContact(QModelIndex const &index)
{
	QList<Contact>	tmp = mModel->getContactList();
	QString	debug("");

	debug += tmp[index.row()].getAccountName();
	debug += tmp[index.row()].getPseudo() + "\n";
	debug += tmp[index.row()].getStatus() + "\n";
	debug += tmp[index.row()].getPassword() + "\n";
	// debug by dialog
	mDialog.setMessage(debug);
	mDialog.show();
}
