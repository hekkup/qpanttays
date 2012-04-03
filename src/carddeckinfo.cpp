// This file is part of QPanttays.
// Licensed under Creative Commons Attribution 3.0 Unported License
// (http://creativecommons.org/licenses/by/3.0/)

#include "carddeckinfo.h"

CardDeckInfo::CardDeckInfo(const QString &name, const QString &fileName, QObject *parent) :
    QObject(parent)
{
	m_name = name;
	m_fileName = fileName;
}

QString CardDeckInfo::name() {
	return m_name;
}

QString CardDeckInfo::fileName() {
	return m_fileName;
}
