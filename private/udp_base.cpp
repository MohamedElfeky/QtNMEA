#include "udp_base.h"
#include "utils.h"

UDPBase::UDPBase() :
    m_pSocket(nullptr),
    m_oAddress(QHostAddress::Any),
    m_uPort(0)
{
}

bool UDPBase::Connect(const QString &sAddress, const QString &sPort)
{
    if (sPort.isEmpty() || !Utils::IsNumber(sPort)) return false;

    m_pSocket = QUdpSocketPtr::create();
    m_uPort = sPort.toUInt();

    if(!sAddress.isEmpty() && Utils::IsIpAddress(sAddress)) {
        m_oAddress.setAddress(sAddress);
    }

    return m_pSocket->bind(m_oAddress, m_uPort);
}

