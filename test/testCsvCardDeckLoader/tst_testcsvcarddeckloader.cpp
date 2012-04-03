#include <QtCore/QString>
#include <QtTest/QtTest>
#include "csvcarddeckloader.h"

class TestCsvCardDeckLoader : public QObject
{
	Q_OBJECT
	
public:
	TestCsvCardDeckLoader();
	
private Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();
	void testParseLine();
	void testMakeCard();
	void testLoadDeck();

private:
	CsvCardDeckLoader* m_loader;
};

TestCsvCardDeckLoader::TestCsvCardDeckLoader()
{
}

void TestCsvCardDeckLoader::initTestCase()
{
	m_loader = new CsvCardDeckLoader();
	QVERIFY(m_loader != NULL);
}

void TestCsvCardDeckLoader::cleanupTestCase()
{
	if (m_loader) {
		delete m_loader;
		m_loader = NULL;
	}
}

void TestCsvCardDeckLoader::testParseLine()
{
	QStringList* card;

	//qDebug() << "empty string";
	card = m_loader->parseLine("");
	QVERIFY(card->at(0) == "");
	card->clear();
	delete card;

	//qDebug() << "one word";
	card = m_loader->parseLine("moro");
	QVERIFY(card->count() == 1);
	QVERIFY(card->at(0) == "moro");
	card->clear();
	delete card;

	//qDebug() << "one word with a comma";
	card = m_loader->parseLine("moro,heippa");
	QVERIFY(card->count() == 1);
	QVERIFY(card->at(0) == "moro,heippa");
	card->clear();
	delete card;

	//qDebug() << "two words";
	card = m_loader->parseLine("\"moro\",\"heippa\"");
	QVERIFY(card->count() == 2);
	QVERIFY(card->at(0) == "moro");
	QVERIFY(card->at(1) == "heippa");
	card->clear();
	delete card;

	// const char[]
	//qDebug() << "three words";
	card = m_loader->parseLine("\"moro\",\"heippa\",\"fact3\"");
	QVERIFY(card->count() == 3);
	QVERIFY(card->at(0) == "moro");
	QVERIFY(card->at(1) == "heippa");
	QVERIFY(card->at(2) == "fact3");
	card->clear();
	delete card;

	// QString
	//qDebug() << "three words";
	card = m_loader->parseLine(QString("\"moro\",\"heippa\",\"fact3\""));
	QVERIFY(card->count() == 3);
	QVERIFY(card->at(0) == "moro");
	QVERIFY(card->at(1) == "heippa");
	QVERIFY(card->at(2) == "fact3");
	card->clear();
	delete card;

	//qDebug() << "two quoted words";
	card = m_loader->parseLine("\"\"\"moro\"\"\",\"\"\"heippa\"\"\"");
	QVERIFY(card->count() == 2);
	QVERIFY(card->at(0) == "moro");
	QVERIFY(card->at(1) == "heippa");
	card->clear();
	delete card;
}

void TestCsvCardDeckLoader::testMakeCard()
{
	QStringList* facts = NULL;
	QVariantList* card = NULL;

	// null fact list
	card = m_loader->makeCard(facts);
	QVERIFY(NULL == card);

	facts = new QStringList();
	QVERIFY(facts != NULL);

	// non-null but empty fact list
	card = m_loader->makeCard(facts);
	QVERIFY(NULL == card);

	facts->append("fact1");
	facts->append("fact2");
	facts->append("fact3");

	// non-empty fact list
	card = m_loader->makeCard(facts);
	QVERIFY(card != NULL);
	QVERIFY(card->count() == 3);
	QVERIFY(card->at(0).toString() == "fact1");
	QVERIFY(card->at(1).toString() == "fact2");
	QVERIFY(card->at(2).toString() == "fact3");

}

void TestCsvCardDeckLoader::testLoadDeck()
{
	QVariantList* deck = NULL;
	QVariantList card;

	// null file name
	deck = m_loader->loadDeck(NULL);
	QVERIFY(NULL == deck);

	// empty file name
	deck = m_loader->loadDeck("");
	QVERIFY(NULL == deck);
	//QVERIFY(deck->isEmpty());

	// non-existing file
	deck = m_loader->loadDeck("heippa.doesnt_exist");
	QVERIFY(NULL == deck);
	//QVERIFY(deck->isEmpty());

	// existing file
	// Assumptions:
	// - file contains total 10 lines
	// - rows 1-2 contain 3 facts -- ok
	// - rows 3-4 contain 2 facts -- should be skipped
	// - row 5 contains 3 facts -- ok
	// - rows 6-7 contain 4 facts -- should be skipped
	// - row 8 contains 5 facts -- should be skipped
	// - rows 9-10 are empty -- should be skipped
	QString fileName(QString(SRCDIR) + QString("../data/dummy_deck_01.csv"));
	//qDebug() << "fileName = " + fileName;
	deck = m_loader->loadDeck(fileName);
	//qDebug() << "deck loaded";
	QVERIFY(deck != NULL);
	QVERIFY(!deck->isEmpty());
	//qDebug() << "deck->count() = " + QString::number(deck->count());
	QVERIFY(deck->count() == 3);
	//QVERIFY(deck.at(0))

	card = deck->at(0).toList();
	//QVERIFY(card != NULL);
	QVERIFY(card.at(0).toString() == "card1_fact1");
	QVERIFY(card.at(1).toString() == "card1_fact2");
	QVERIFY(card.at(2).toString() == "card1_fact3");

	card = deck->at(1).toList();
	//QVERIFY(card != NULL);
	QVERIFY(card.at(0).toString() == "card2_fact1");
	QVERIFY(card.at(1).toString() == "card2_fact2");
	QVERIFY(card.at(2).toString() == "card2_fact3");

	card = deck->at(2).toList();
	//QVERIFY(card != NULL);
	QVERIFY(card.at(0).toString() == "card5_fact1");
	QVERIFY(card.at(1).toString() == "card5_fact2");
	QVERIFY(card.at(2).toString() == "card5_fact3");

}

QTEST_APPLESS_MAIN(TestCsvCardDeckLoader)

#include "tst_testcsvcarddeckloader.moc"
