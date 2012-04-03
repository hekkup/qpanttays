#-------------------------------------------------
#
# Project created by QtCreator 2012-02-26T16:16:45
#
#-------------------------------------------------

QT       += testlib
QT       -= gui
QT       += declarative

TARGET = tst_testqpanttaysdatamanagertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

#include(../../qmlapplicationviewer/qmlapplicationviewer.pri)

INCLUDEPATH += ../../src/ \
  ../../qmlapplicationviewer \
  ../mock

SOURCES += tst_testqpanttaysdatamanagertest.cpp \
  ../../src/qpanttaysdatamanager.cpp \
  ../../src/carddecklistmodel.cpp \
  ../../src/carddeckinfo.cpp \
  ../../src/csvcarddeckloader.cpp \
  ../mock/mock_qmlapplicationviewer.cpp \
  #../../qmlapplicationviewer.cpp



HEADERS += ../../src/qpanttaysdatamanager.h \
  ../../src/carddecklistmodel.h \
  ../../src/carddeckinfo.h \
  ../../src/csvcarddeckloader.h \
  ../../qmlapplicationviewer/qmlapplicationviewer.h

DEFINES += SRCDIR=\\\"$$PWD/\\\" \
  _UNIT_TEST_ \
  TEST_CARD_DECK_FILE=\"../data/dummy_deck_01.csv\"


OTHER_FILES += ../data/dummy_deck_01.csv \
	MockMainPage.qml
