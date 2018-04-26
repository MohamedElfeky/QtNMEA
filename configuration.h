/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "types.h"
#include <QString>

/*
 * Configuration for command line
 */
class Configuration
{
public:
    Configuration();
    Configuration(int argc, char* argv[]);

    /*
     * Find keywords in params
     * --server | --client
     * -i ip_address
     * -p port
     */
    void Initialize(int argc, char* argv[]);
    inline ApplicationMode GetMode() const { return m_eMode; }
    inline QString GetAddress() const { return m_sAddress; }
    inline QString GetPort() const { return m_sPort; }

private:
    ApplicationMode m_eMode;
    QString m_sAddress;
    QString m_sPort;
};

#endif // CONFIGURATION_H
