// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#include "qpanttaysdatamanager.h"

QPanttaysDataManager::QPanttaysDataManager(QObject *parent) :
	QObject(parent)
{
	m_applicationViewer = NULL;
	m_cardDeckListModel = NULL;
    m_cardDeckConfig = NULL;
}

QPanttaysDataManager::~QPanttaysDataManager() {
	if (this->m_cardDeckListModel) {
		m_cardDeckListModel->~CardDeckListModel();
        m_cardDeckListModel = NULL;
	}
    if (this->m_cardDeckConfig) {
        delete m_cardDeckConfig;
        m_cardDeckConfig = NULL;
    }
}

bool QPanttaysDataManager::init(QmlApplicationViewer *applicationViewer) {
	if (!applicationViewer) {
		return false;
	}
	CardDeckListModel* deckListModel = new CardDeckListModel();
	if (!deckListModel) {
		return false;
	}
    this->m_applicationViewer = applicationViewer;

    CardDeckInfo * deckInfo = NULL;

	// Add files from data directories in home and MYDOCS_DIR

    // First home (~/QPANTTAYS_DIR)
    QString pathToHomeDataDir = QDir::homePath() + "/" + QPANTTAYS_DIR;
	QDir homeDataDir(pathToHomeDataDir);
	QStringList fileNameFilter;
    fileNameFilter.append("*.csv");
	QFileInfoList fileList;

	if (homeDataDir.exists()) {
		fileList.append(homeDataDir.entryInfoList(fileNameFilter, QDir::Files, QDir::Name | QDir::IgnoreCase));
	}

    // Then ~/MYDOCS_DIR/QPANTTAYS_DIR
    QString pathToMyDocsDataDir = QDir::homePath() + "/" + QString(MYDOCS_DIR) + "/" + QPANTTAYS_DIR;
	QDir myDocsDataDir(pathToMyDocsDataDir);
	if (myDocsDataDir.exists()) {
		fileList.append(myDocsDataDir.entryInfoList(fileNameFilter, QDir::Files, QDir::Name | QDir::IgnoreCase));
	}

	// add files to deck model
	QListIterator<QFileInfo> fileListIt(fileList);
	while (fileListIt.hasNext()) {
		QFileInfo finfo = fileListIt.next();
		QString fname = finfo.baseName();
		QString fpath = finfo.absoluteFilePath();
		deckInfo = new CardDeckInfo(fname, fpath);
		if (deckInfo) {
			deckListModel->add(deckInfo);
		}
	}

	this->m_cardDeckListModel = deckListModel;

	QDeclarativeContext * ctx = this->m_applicationViewer->rootContext();

	ctx->setContextProperty("cardDeckListModel", this->m_cardDeckListModel);
	ctx->setContextProperty("dataManager", this);

	//connect(ctx, SIGNAL(flashCardPageLoaded(int)), this, SLOT(onFlashCardPageLoaded(int)));

    if (!this->m_cardDeckConfig) {
        //qDebug() << "loading card deck config "+QString::number(cardDeckIndex);
        this->m_cardDeckConfig = new QVariantList();
        this->m_cardDeckConfig->append(QVariant(true));
        this->m_cardDeckConfig->append(QVariant(false));
        this->m_cardDeckConfig->append(QVariant(false));
    }

	return true;
}

//void QPanttaysDataManager::setCardDeckListModel(CardDeckListModel* cardDeckListModel) {
//	this->m_cardDeckListModel = cardDeckListModel;
//}

QVariantList* QPanttaysDataManager::loadCardDeck(int cardDeckIndex) {
	if (!this->m_cardDeckListModel) {
		// not initialized
		return NULL;
    }
	QModelIndex index = this->m_cardDeckListModel->index(cardDeckIndex);
	QString fileName = (this->m_cardDeckListModel->data(index, CardDeckListModel::FileNameRole)).toString();
	//QString fileName = homePath + dataDirInHome + fileBaseName;
    //qDebug() << "Loading file: "+fileName;
	CsvCardDeckLoader * cardDeckLoader = new CsvCardDeckLoader();
	if (!cardDeckLoader) {
		return NULL;
	}
	QVariantList* deck = cardDeckLoader->loadDeck(fileName);
	if (!deck) {
		return NULL;
	}
    //qDebug() << "Deck loaded";
	return deck;
	//return NULL;
}

void QPanttaysDataManager::loadCardDeckConfig(int cardDeckIndex) {
    QDeclarativeContext* ctx = this->m_applicationViewer->rootContext();
    ctx->setContextProperty("cardDeckConfig", *(this->m_cardDeckConfig));
    //qDebug() << "QPanttaysDataManager::loadCardDeckConfig("+QString::number(cardDeckIndex)+") done";
}

void QPanttaysDataManager::setLargeFactFont(int factIndex, bool value) {
    //qDebug() << "QPanttaysDataManager::setLargeFactFont("+QString::number(factIndex)+", "+ (value?"true":"false") + ")";
    if (!this->m_cardDeckConfig) {
        this->loadCardDeckConfig(0);
    }
    QVariant tmpVariant = QVariant(value);
    this->m_cardDeckConfig->replace(factIndex, tmpVariant);
    //qDebug() << "QPanttaysDataManager: cardDeckConfig[" +
    //            QString::number(factIndex)+"] is now: " +
    //            (this->m_cardDeckConfig->at(factIndex).toBool() ? "true" : "false");

    /// @todo check if really necessary to write back the config
    QDeclarativeContext* ctx = this->m_applicationViewer->rootContext();
    ctx->setContextProperty("cardDeckConfig", *(this->m_cardDeckConfig));
}

void QPanttaysDataManager::flashCardPageLoaded(int cardDeckIndex) {
    QVariantList* deck = NULL;
    deck = this->loadCardDeck(cardDeckIndex);
    QDeclarativeContext* ctx = this->m_applicationViewer->rootContext();
    if (deck) {
        ctx->setContextProperty("wordList", *deck);
	}
}

