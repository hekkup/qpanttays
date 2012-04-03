#include <QtCore/QString>
#include <QtTest/QtTest>
#include "carddeckinfo.h"

/**
 * @brief CardDeckInfo unit test
 */
class TestCardDeckInfo : public QObject
{
	Q_OBJECT
	
public:
	TestCardDeckInfo();
	
private Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();
	void testName();
	void testFileName();

private:
	CardDeckInfo * m_deckInfo;
};

TestCardDeckInfo::TestCardDeckInfo()
{
}

void TestCardDeckInfo::initTestCase()
{
	m_deckInfo = new CardDeckInfo("dummyDeck", "dummyFileName");
	QVERIFY(m_deckInfo != NULL);
}

void TestCardDeckInfo::cleanupTestCase()
{
	delete m_deckInfo;
	m_deckInfo = NULL;
}

void TestCardDeckInfo::testName()
{
	QVERIFY(m_deckInfo->m_name == "dummyDeck");
	QVERIFY(m_deckInfo->name() == "dummyDeck");
}

void TestCardDeckInfo::testFileName()
{
	QVERIFY(m_deckInfo->m_fileName == "dummyFileName");
	QVERIFY(m_deckInfo->fileName() == "dummyFileName");
}

QTEST_APPLESS_MAIN(TestCardDeckInfo)
//QTEST_MAIN(TestCardDeckInfo)

#include "tst_testcarddeckinfo.moc"
