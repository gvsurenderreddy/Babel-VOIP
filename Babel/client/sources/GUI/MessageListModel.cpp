#include "MessageListModel.hpp"

MessageListModel::MessageListModel(QObject *parent)
	: QAbstractListModel(parent)
{

}

MessageListModel::~MessageListModel()
{
}

int		MessageListModel::rowCount(const QModelIndex &/*parent*/) const
{
	return mMessageList.size();
}

QVariant	MessageListModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() >= mMessageList.size())
		return QVariant();

	if (role == Qt::DisplayRole)
	{
        QString	data("[" + mMessageList[index.row()].autor + "]: " + mMessageList[index.row()].msg);

		return data;
	}

	return QVariant();
}

QVariant	MessageListModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
	return QVariant();
}

bool	MessageListModel::compare(Contact::Message const &v1, Contact::Message const &v2)
{
	return (v1.datetime.toString() < v2.datetime.toString());
}

void	MessageListModel::sort()
{
	qSort(mMessageList.begin(), mMessageList.end(), compare);
}

