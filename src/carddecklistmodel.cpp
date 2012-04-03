// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#include "carddecklistmodel.h"

CardDeckListModel::CardDeckListModel(QObject* parent) :
	QAbstractListModel(parent)
{
	m_cardDeckInfoList.empty();

	QHash<int, QByteArray> roleNames;
	roleNames[CardDeckListModel::NameRole] = "name";
	roleNames[CardDeckListModel::FileNameRole] = "fileName";
	setRoleNames(roleNames);
}

CardDeckListModel::~CardDeckListModel() {
	QListIterator<CardDeckInfo*> listIt(m_cardDeckInfoList);
	while (listIt.hasNext()) {
		CardDeckInfo* deckInfo = listIt.next();
		delete deckInfo;
		deckInfo = NULL;
	}
	m_cardDeckInfoList.empty();
}

void CardDeckListModel::add(CardDeckInfo* cardDeckInfo) {
	if (cardDeckInfo) {
		this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
		m_cardDeckInfoList.append(cardDeckInfo);
		this->endInsertRows();
	}
}

int CardDeckListModel::rowCount(const QModelIndex& parent) const {
	parent.isValid();	// just to get rid of unused parameter warning...
	return m_cardDeckInfoList.count();
}

QVariant CardDeckListModel::data(const QModelIndex& index, int role) const {
	if ((index.row() < 0) || (index.row() >= m_cardDeckInfoList.count())) {
		return QVariant::Invalid;
	}
	CardDeckInfo * deckInfo = m_cardDeckInfoList.at(index.row());
	switch(role) {
	case CardDeckListModel::NameRole: {
		if (deckInfo) {
			return QVariant(deckInfo->name());
		}
		break;
	}
	case CardDeckListModel::FileNameRole: {
		if (deckInfo) {
			return QVariant(deckInfo->fileName());
		}
		break;
	}
	} // switch
	return QVariant::Invalid;
}
