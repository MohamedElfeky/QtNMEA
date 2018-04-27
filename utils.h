/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef UTILS_H
#define UTILS_H

#include <QString>

/*
 * Class provides static function to check string values
 */
class Utils
{
public:
    // String contains only digits (not exact number)
    static bool IsNumber(const QString& sTest);
    // String matches mask \d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}
    static bool IsIpAddress(const QString& sAddress);
    // Check string to mask COM{N}
    static bool IsComPort(const QString& sAddress);
};

#endif // UTILS_H
