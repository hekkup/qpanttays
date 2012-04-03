// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#ifndef _CARD_DECK_LIST_MODEL_H_
#define _CARD_DECK_LIST_MODEL_H_

#include <QAbstractListModel>
#include <QHash>
#include "carddeckinfo.h"

/**
 * @brief CardDeckInfo list model
 */
class CardDeckListModel : public QAbstractListModel
{
	Q_OBJECT
public:

	enum CardDeckRoles {
		NameRole = Qt::UserRole + 1,
		FileNameRole
	};

	explicit CardDeckListModel(QObject* parent = 0);

	~CardDeckListModel();

	void add(CardDeckInfo* cardDeckInfo);

	//bool exists(CardDeckInfo* cardDeckInfo);

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;

	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	
//signals:
	
//public slots:

private:
	QList<CardDeckInfo*> m_cardDeckInfoList;
	
};

#endif // _CARD_DECK_LIST_MODEL_H_
