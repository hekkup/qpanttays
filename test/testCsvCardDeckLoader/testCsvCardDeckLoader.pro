#-------------------------------------------------
#
# Project created by QtCreator 2012-02-23T23:58:04
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testcsvcarddeckloader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += "../../src"

SOURCES += tst_testcsvcarddeckloader.cpp \
  ../../src/csvcarddeckloader.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\" \
  _UNIT_TEST_

HEADERS += ../../src/csvcarddeckloader.h

OTHER_FILES += ../data/dummy_deck_01.csv
