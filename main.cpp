// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#include <QtGui/QApplication>
#include <QDebug>
#include "qmlapplicationviewer.h"
#include "qpanttaysdatamanager.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

	QmlApplicationViewer viewer;

	QPanttaysDataManager dataManager;
	bool ok = dataManager.init(&viewer);
	if (!ok) {
		qDebug() << "Failed to set data manager";
	}

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/qpanttays/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
