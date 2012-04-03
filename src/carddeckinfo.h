// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#ifndef _CARD_DECK_INFO_H_
#define _CARD_DECK_INFO_H_

#include <QObject>

/**
 * @brief Card deck information
 */
class CardDeckInfo : public QObject
{
	Q_OBJECT
public:
	explicit CardDeckInfo(const QString& name, const QString& fileName, QObject *parent = 0);

//signals:
//public slots:

	/**
	 * @return card deck name
	 */
	QString name();

	/**
	 * This method returns the name of the data file in which the card data
	 * of this deck is stored.
	 *
	 * @return name of card data file
	 */
	QString fileName();

#ifndef _UNIT_TEST_
private:
#endif
	QString m_name;			///< card deck name
	//int m_numberOfCards;	///< number of cards in this deck
	//int m_numberOfFacts;	///< number of facts ("sides") in card
	QString m_fileName;		///< name of card data file
};

#endif // _CARD_DECK_INFO_H_
