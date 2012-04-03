#-------------------------------------------------
#
# Project created by QtCreator 2012-02-23T01:03:21
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testcarddeckinfo
#CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += _UNIT_TEST_

SOURCES += tst_testcarddeckinfo.cpp \
  ../../src/carddeckinfo.cpp

INCLUDEPATH += ../../src

HEADERS += ../../src/carddeckinfo.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
