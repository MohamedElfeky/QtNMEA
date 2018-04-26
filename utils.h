#ifndef UTILS_H
#define UTILS_H

#include <QString>

class Utils
{
public:
    static bool IsNumber(const QString& sTest);
    static bool IsIpAddress(const QString& sAddress);
};

#endif // UTILS_H
