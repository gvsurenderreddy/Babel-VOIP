#pragma once

#include <QtWidgets/QWidget>
#include <QAbstractListModel>
#include <QListView>
#include <QList>
#include "Contact.hpp"

class MessageListModel : public QAbstractListModel
{
	// ctor - dtor
	public:
		MessageListModel(QObject *parent = nullptr);
		~MessageListModel();

	// coplien form
	private:
		MessageListModel(const MessageListModel &) : QAbstractListModel(nullptr) {}
		const MessageListModel &operator=(const MessageListModel &) { return *this; }

	// attributs
	private:
		QList<Contact::Message>	mMessageList;

	// methods
	public:
		int				rowCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant		data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant		headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		void						setMessageList(QList<Contact::Message> const &messageList) { beginResetModel(); mMessageList = messageList; endResetModel(); }
		QList<Contact::Message> 	&getMessageList() { return mMessageList; }
		void						sort();

		static bool		compare(Contact::Message const &v1, Contact::Message const &v2);
};
