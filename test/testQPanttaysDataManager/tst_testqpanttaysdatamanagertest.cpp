#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtDeclarative>
#include "qpanttaysdatamanager.h"
#include "qmlapplicationviewer.h"

class TestQPanttaysDataManagerTest : public QObject
{
	Q_OBJECT
	
public:
	TestQPanttaysDataManagerTest();
	
private Q_SLOTS:
	void initTestCase();
	void cleanupTestCase();
	void testLoadCardDeck();

private:
	QPanttaysDataManager* m_dataManager;
};

TestQPanttaysDataManagerTest::TestQPanttaysDataManagerTest()
{
	m_dataManager = NULL;
}

void TestQPanttaysDataManagerTest::initTestCase()
{
	QmlApplicationViewer viewerInstance;
	m_dataManager = new QPanttaysDataManager();
	QVERIFY(m_dataManager != NULL);
}

void TestQPanttaysDataManagerTest::cleanupTestCase()
{
	if (m_dataManager) {
		delete m_dataManager;
		m_dataManager = NULL;
	}
}

void TestQPanttaysDataManagerTest::testLoadCardDeck()
{
	//QmlApplicationViewer testViewer;

	//testViewer.setMainQmlFile("MockMainPage.qml");
	//QVERIFY(m_dataManager->init(&testViewer));

	/*QVariantList* deck = NULL;

	CardDeckListModel* listModel = new CardDeckListModel();
	QVERIFY(listModel != NULL);

	CardDeckInfo * deckInfo = NULL;
	qDebug() << QString(SRCDIR);
	qDebug() << QString(TEST_CARD_DECK_FILE);
	QString testDeckFileName = QString(QString(SRCDIR) + QString(TEST_CARD_DECK_FILE));
	deckInfo = new CardDeckInfo("testDeck1", "deck_doesnt_exist.csv");
	if (deckInfo) {
		listModel->add(deckInfo);
	}
	deckInfo = new CardDeckInfo("testDeck2", "\""+testDeckFileName+"\"");
	if (deckInfo) {
		listModel->add(deckInfo);
	}

	m_dataManager->setCardDeckListModel(listModel);

	deck = m_dataManager->loadCardDeck(0);
	QVERIFY(NULL == deck);

	deck = m_dataManager->loadCardDeck(1);
	QVERIFY(NULL != deck);*/

}

QTEST_APPLESS_MAIN(TestQPanttaysDataManagerTest)

#include "tst_testqpanttaysdatamanagertest.moc"
