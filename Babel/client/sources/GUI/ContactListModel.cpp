#include "ContactListModel.hpp"

ContactListModel::ContactListModel(QObject *parent)
	: QAbstractListModel(parent)
{

}

ContactListModel::~ContactListModel()
{
}

int						ContactListModel::rowCount(const QModelIndex &/*parent*/) const
{
	return mContactList.size();
}

QVariant				ContactListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= mContactList.size())
		return QVariant();

	if (role == Qt::DisplayRole)
		return mContactList[index.row()].getPseudo();

	return QVariant();
}

QVariant				ContactListModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
	return QVariant();
}

bool					ContactListModel::compare(Contact const &v1, Contact const &v2)
{
	return (v1.getPseudo() < v2.getPseudo());
}

void					ContactListModel::sort()
{
	qSort(mContactList.begin(), mContactList.end(), compare);
}

