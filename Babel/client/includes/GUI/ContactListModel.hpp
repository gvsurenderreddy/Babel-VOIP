#pragma once

#include <QtWidgets/QWidget>
#include <QAbstractListModel>
#include <QList>
#include <QListView>
#include "Contact.hpp"

class ContactListModel : public QAbstractListModel
{
	// ctor - dtor
	public:
		ContactListModel(QObject *parent = nullptr);
		~ContactListModel();

	// coplien form
	private:
		ContactListModel(const ContactListModel &) : QAbstractListModel(nullptr) {}
		const ContactListModel &operator=(const ContactListModel &) { return *this; }

	// attributs
	private:
		QList<Contact>			mContactList;

	// methods
	public:
		int						rowCount(const QModelIndex &parent = QModelIndex()) const;
		QVariant				data(const QModelIndex &index, int role = Qt::DisplayRole) const;
		QVariant				headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

		void					setModelList(QList<Contact> const &contactList);
		QList<Contact> const	&getListModel() const { return mContactList; }
		void					sort();

		static bool				compare(Contact const &v1, Contact const &v2);
};
