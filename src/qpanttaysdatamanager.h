// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#ifndef _QPANTTAYS_DATA_MANAGER_H_
#define _QPANTTAYS_DATA_MANAGER_H_

#include <QObject>
#include <QDeclarativeContext>
#include <QDir>
#include <qmlapplicationviewer.h>
#include "carddeckinfo.h"
#include "carddecklistmodel.h"
#include "csvcarddeckloader.h"

/// @todo get platform-dependent user docs directory
#define MYDOCS_DIR "MyDocs"		///< user documents directory (in Meego/Harmattan)
#define QPANTTAYS_DIR ".qpanttays"	///< data directory, should be found in MYDOCS_DIR and/or home
#define CONFIG_FILE "qpanttays.conf"    ///< configuration file, resides in QPANTTAYS_DIR

/**
 * @brief QPanttays data manager
 *
 * This class shuffles data from and to QPanttays.
 * Call init() to set things up.
 */
class QPanttaysDataManager : public QObject
{
	Q_OBJECT
public:
	explicit QPanttaysDataManager(QObject *parent = 0);
	~QPanttaysDataManager();
	
	/**
	 * Initialize data, put data into QmlApplicationViewer.
	 *
	 * @return true on success, false on failure
	 */
	bool init(QmlApplicationViewer * applicationViewer);

	/**
	 * Load card deck. Card deck index is the index in the
	 * internal card deck list model.
	 *
	 * @param cardDeckIndex index of card deck in internal card deck list
	 */
	QVariantList* loadCardDeck(int cardDeckIndex);

    /**
     * Load card deck configuration. Card deck index is the index
     * in the internal card deck list model.
     */
    //void loadCardDeckConfiguration(int cardDeckIndex);


//signals:
	
//public slots:

	/**
	 * Load card deck with index and give it to FlashCardPage.
	 *
	 * @todo clarify signals/slots/callbacks here
	 * Problem is cannot connect to signal from QML because page
	 * is created on-demand
	 *
	 * @param cardDeckIndex index of card deck in internal card deck list
	 */
	Q_INVOKABLE void flashCardPageLoaded(int cardDeckIndex);

    Q_INVOKABLE void setLargeFactFont(int factIndex, bool value);

    Q_INVOKABLE void loadCardDeckConfig(int cardDeckIndex);

#ifndef _UNIT_TEST_
private:
#endif
	QmlApplicationViewer* m_applicationViewer;
	CardDeckListModel* m_cardDeckListModel;

    QVariantList* m_cardDeckConfig;

	//void setCardDeckListModel(CardDeckListModel* cardDeckListModel);
};

#endif // _QPANTTAYS_DATA_MANAGER_H_
