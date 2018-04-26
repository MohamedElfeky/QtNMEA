#ifndef UDP_BASE_H
#define UDP_BASE_H

#include <QUdpSocket>

typedef QSharedPointer<QUdpSocket> QUdpSocketPtr;

class UDPBase
{
public:
    UDPBase();
    virtual ~UDPBase(){}
    bool Connect(const QString& sAddress, const QString& sPort);

protected:
    QUdpSocketPtr m_pSocket;
    QHostAddress m_oAddress;
    quint16 m_uPort;
};

#endif // UDP_BASE_H
