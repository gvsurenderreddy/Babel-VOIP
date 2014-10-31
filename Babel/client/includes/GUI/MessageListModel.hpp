#pragma once

#include <QtWidgets/QWidget>
#include <QAbstractListModel>
#include <QDateTime>
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

	// structure of message
	public:
		struct sMessage
		{
			QString		autor;
			QString		msg;
			QDateTime	datetime;
		};

	// attributs
	private:
		QList<sMessage>	mMessageList;

	// methods
	public:
		int				rowCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant		data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant		headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		void			setContactList(QList<sMessage> const &messageList) { mMessageList = messageList; }
		QList<sMessage> 	&getContactList() { return mMessageList; }
		void			sort();

		static bool		compare(sMessage const &v1, sMessage const &v2);
};
