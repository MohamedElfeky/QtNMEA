/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef UDP_BASE_H
#define UDP_BASE_H

#include <QUdpSocket>

typedef QSharedPointer<QUdpSocket> QUdpSocketPtr;

/*
 * Class provides base connection to UDP socket
 */
class UDPBase
{
public:
    UDPBase();
    virtual ~UDPBase(){}
    bool Connect(const QString& sAddress, const QString& sPort);
    bool IsValid() const;

protected:
    QUdpSocketPtr m_pSocket;
    QHostAddress m_oAddress;
    quint16 m_uPort;
};

#endif // UDP_BASE_H
