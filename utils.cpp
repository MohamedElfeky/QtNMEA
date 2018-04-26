/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "utils.h"
#include <QRegExp>

bool Utils::IsNumber(const QString &sTest)
{
    QRegExp oRegExp("\\d*");
    return oRegExp.exactMatch(sTest);
}

bool Utils::IsIpAddress(const QString &sAddress)
{
    QRegExp oRegExp("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
    return oRegExp.exactMatch(sAddress);
}
