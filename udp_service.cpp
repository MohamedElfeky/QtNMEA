#include "udp_service.h"
#include "utils.h"
#include <QDataStream>

typedef QSharedPointer<QUdpSocket> QUdpSocketPtr;
typedef QSharedPointer<QHostAddress> QHostAddressPtr;

UDPService::UDPService(QObject *parent) :
    QObject(parent),
    m_pSocket(nullptr),
    m_oAddress(QHostAddress::Any),
    m_uPort(0),
    m_eMode(ApplicationMode::SERVER)
{
}

bool UDPService::Initialize(const QString &sAddress, const QString &sPort, ApplicationMode eMode)
{
    if (sPort.isEmpty() || !Utils::IsNumber(sPort) || eMode == ApplicationMode::STANDALONE) return false;

    m_pSocket = QUdpSocketPtr::create();
    m_uPort = sPort.toUInt();

    if(!sAddress.isEmpty() && Utils::IsIpAddress(sAddress)) {
        m_oAddress.setAddress(sAddress);
    }

    m_eMode = eMode;
    return Connect();
}

bool UDPService::Send(const QString &sMessage)
{
    if (!m_pSocket || sMessage.isEmpty()) return false;

    QByteArray oDatagram(sMessage.toUtf8());
    qint64 iSize = m_pSocket->writeDatagram(oDatagram, m_oAddress, m_uPort);

    return iSize > 0;
}

void UDPService::MessageSend(const QString &sMessage)
{
    Send(sMessage);
}

void UDPService::ReadSocket()
{
    if(!m_pSocket) return;

    QByteArray oDatagram(m_pSocket->pendingDatagramSize(), '\0'); // size by pending datagram
    QHostAddressPtr pHost = QHostAddressPtr::create();

    m_pSocket->readDatagram(oDatagram.data(), oDatagram.size(), &m_oAddress, &m_uPort);

    QString sMessage(oDatagram);
    emit MessageReceived(sMessage);
}

bool UDPService::Connect()
{
    if(!m_pSocket) return false;

    m_pSocket->bind(m_oAddress, m_uPort);

    if (m_eMode == ApplicationMode::SERVER)
        connect(m_pSocket.data(), SIGNAL(readyRead()), this, SLOT(ReadSocket()));

    return true;
}
