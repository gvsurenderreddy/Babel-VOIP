#include "BabelMain.hpp"

BabelMain::BabelMain()
	: QWidget()
{
	mUi.setupUi(this);
	mModel = new ContactListModel(this);

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

}
