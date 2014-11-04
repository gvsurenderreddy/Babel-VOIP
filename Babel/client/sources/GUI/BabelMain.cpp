#include "BabelMain.hpp"

BabelMain::BabelMain()
	: QWidget(), mNewContact(""), mIsCall(false)
{
	mUi.setupUi(this);

	mModel = new ContactListModel(this);
	mMessages = new MessageListModel(this);
	mUi.listContactView->setModel(mModel);

	mOriginalSize = size();

	// Event on list contact
	QObject::connect(mUi.listContactView, SIGNAL(clicked(QModelIndex const &)), this, SLOT(onClickContact(QModelIndex const &)));
	QObject::connect(mUi.addContact, SIGNAL(clicked()), this, SLOT(onClickAddContact()));
}

BabelMain::~BabelMain()
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

void		BabelMain::onClickContact(QModelIndex const &index)
{
	mUi.name->setText(mModel->getContactList()[index.row()].getAccountName());
	mCurrentContact = mModel->getContactList()[index.row()];
}

void		BabelMain::onClickAddContact()
{
	mDialog.setMessage("Envoie de la demande d'ami ;)");
	mDialog.show();
}
