// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#ifndef _CSV_CARD_DECK_LOADER_H_
#define _CSV_CARD_DECK_LOADER_H_

#include <QObject>
#include <QVariantList>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QRegExp>

/**
 * Implement CardDeckLoader interface
 */
class CsvCardDeckLoader : public QObject
{
	Q_OBJECT
public:
	explicit CsvCardDeckLoader(QObject* parent = 0);

	/**
	 * Load card deck from CSV file.
	 * The returned card deck is a QVariantList so that each variant (card) contains
	 * another QVariantList containing the card facts.
	 * All cards will have the same amount of facts.
	 *
	 * @param fileName file name
	 * @return QVariantList containing the loaded deck, or NULL if file was invalid.
	 */
	QVariantList* loadDeck(const QString& fileName);

#ifndef _UNIT_TEST_
private:
#endif

	/**
	 * Parse a single line.
	 *
	 * @param line line to parse
	 * @return QStringList containing comma separated items found from the given line, or NULL if line was invalid.
	 */
	QStringList* parseLine(const QString& line);

	/**
	 * Make a card (QVariantList) out of facts (QStringList).
	 *
	 * @param factList list of facts
	 * @return factList converted into deck
	 */
	QVariantList* makeCard(QStringList* factList);
};

#endif // _CSV_CARD_DECK_LOADER_H_
