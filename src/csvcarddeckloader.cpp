// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#include "csvcarddeckloader.h"

CsvCardDeckLoader::CsvCardDeckLoader(QObject *parent) :
	QObject(parent)
{
}


QVariantList* CsvCardDeckLoader::loadDeck(const QString& fileName) {
	int numFacts = -1;
	QFile file(fileName);
	QVariantList* tmpCard = NULL;
	QVariantList* tmpDeck = NULL;
	bool ok = false;
	QByteArray rawLine;
	QStringList* facts = NULL;

	if (!file.exists(fileName)) {
		qDebug() << "File '" + fileName +"' doesn't exist";
		return NULL;
	}

	ok = file.open(QFile::ReadOnly | QFile::Text);
	if (!ok) {
		qDebug() << "Error opening file '" + fileName + "'";
		return NULL;
	}

	tmpDeck = new QVariantList();
	if (!tmpDeck) {
		return NULL;
	}

	while (!file.atEnd()) {
		rawLine = file.readLine();
		rawLine = rawLine.trimmed();
		if (rawLine.length() == 0) {
			continue;
		}
		QString line = QString::fromUtf8(rawLine.data());
		//qDebug() << line;
		facts = this->parseLine(line);
		if (facts && !facts->isEmpty()) {

			// take fact count from the first line
			if ((facts->count() > 0) && (-1 == numFacts)) {
				numFacts = facts->count();
			}
			//else {
			//	return tmpDeck;
			//}
			// fact count must be the same for every line
			if (facts->count() == numFacts) {
				// fact count ok, make and add card
				tmpCard = this->makeCard(facts);
				if (tmpCard) {
					tmpDeck->append(QVariant(*tmpCard));
				}
			}
			delete facts;
		} else {
			// error parsing line
		}
	}
	//qDebug() << "All lines in file parsed";
	return tmpDeck;
}

QStringList* CsvCardDeckLoader::parseLine(const QString& line) {
	// format: "fact1","fact2a, fact2b","fact3a, fact3b"
	QRegExp separatorsExp("\",\"");
	QStringList* sList = new QStringList(line.split(separatorsExp));
	QMutableStringListIterator sListIt(*sList);
	while (sListIt.hasNext()) {
		QString str = sListIt.next();
		str = str.trimmed();
		// remove quotes from string ends
		/// @todo should check whether quotes actually belong to the string
		while (str.startsWith('"')) {
			str.remove(0, 1);
		}
		while (str.endsWith('"')) {
			str.remove(str.length() - 1, 1);
		}
		sListIt.setValue(str);
	}
	return sList;
}

QVariantList* CsvCardDeckLoader::makeCard(QStringList* factList) {
	if (!factList) {
		return NULL;
	}
	QVariantList* tmpCard = NULL;
	if (factList->isEmpty()) {
		return NULL;
	}

	tmpCard = new QVariantList();
	if (!tmpCard) {
		return NULL;
	}
	//qDebug() << "New card";
	QStringListIterator factIterator(*factList);
	while (factIterator.hasNext()) {
		QString factStr = factIterator.next();
		tmpCard->append(QVariant(factStr));
		//qDebug() << "   "+factStr;
	}
	return tmpCard;
}
