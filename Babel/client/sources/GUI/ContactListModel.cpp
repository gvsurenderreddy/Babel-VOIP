#include "ContactListModel.hpp"

ContactListModel::ContactListModel(QObject *parent)
	: QAbstractListModel()
{
}

ContactListModel::~ContactListModel()
{
}

int						ContactListModel::rowCount(const QModelIndex &parent = QModelIndex()) const
{
	mContactList.size();
}

QVariant				ContactListModel::data(const QModelIndex &index, int role = Qt::DisplayRole) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= mContactList.size())
		return QVariant();

	if (role == Qt::DisplayRole)
		return QVariant(mContactList[index.row()].getPseudo());
	return QVariant();
}

QVariant				ContactListModel::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
{
	return QVariant();
}

void					ContactListModel::setModelList(QList<Contact> const &contactList)
{
	mContactList = contactList;
}

bool					ContactListModel::compare(Contact const &v1, Contact const &v2)
{
	return (v1.getPseudo() < v2.getPseudo());
}

void					ContactListModel::sort()
{
	qSort(mContactList.begin(), mContactList.end(), compare);
}

