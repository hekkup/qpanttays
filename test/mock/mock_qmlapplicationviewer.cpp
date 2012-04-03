#include "qmlapplicationviewer.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>

#include <qplatformdefs.h> // MEEGO_EDITION_HARMATTAN

//#ifdef HARMATTAN_BOOSTER
//#include <MDeclarativeCache>
//#endif

#if defined(QMLJSDEBUGGER) && QT_VERSION < 0x040800

#include <qt_private/qdeclarativedebughelper_p.h>

#if !defined(NO_JSDEBUGGER)
#include <jsdebuggeragent.h>
#endif
#if !defined(NO_QMLOBSERVER)
#include <qdeclarativeviewobserver.h>
#endif

// Enable debugging before any QDeclarativeEngine is created
struct QmlJsDebuggingEnabler
{
	QmlJsDebuggingEnabler()
	{
		//QDeclarativeDebugHelper::enableDebugging();
	}
};

// Execute code in constructor before first QDeclarativeEngine is instantiated
static QmlJsDebuggingEnabler enableDebuggingHelper;

#endif // QMLJSDEBUGGER


QmlApplicationViewer::QmlApplicationViewer(QWidget *parent)
	: QDeclarativeView(parent)
//	, d(new QmlApplicationViewerPrivate())
{
	//connect(engine(), SIGNAL(quit()), SLOT(close()));
	//setResizeMode(QDeclarativeView::SizeRootObjectToView);
	// Qt versions prior to 4.8.0 don't have QML/JS debugging services built in
#if defined(QMLJSDEBUGGER) && QT_VERSION < 0x040800
#if !defined(NO_JSDEBUGGER)
	//new QmlJSDebugger::JSDebuggerAgent(engine());
#endif
#if !defined(NO_QMLOBSERVER)
	//new QmlJSDebugger::QDeclarativeViewObserver(this, this);
#endif
#endif
}

QmlApplicationViewer::~QmlApplicationViewer()
{
	//delete d;
}

void QmlApplicationViewer::setMainQmlFile(const QString &file) {
	this->setSource(file);
}
