/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "udp_client.h"
#include "gpsdata_adapter.h"
#include "ReceiverWindow.h"

UDPClient::UDPClient(QObject *parent) :
    UDPInterface(parent),
    UDPBase()
{
}

bool UDPClient::Initialize(const QString &sAddress, const QString &sPort)
{
    return UDPBase::Connect(sAddress, sPort);
}

void UDPClient::Bind(const GPSDataAdapter &oDataAdapter, const ReceiverWindow &oWindow)
{
    QObject::connect(&oDataAdapter, SIGNAL(Changed(GPSDataAdapter)), &oWindow, SLOT(GPSDataChanged(GPSDataAdapter)));
    QObject::connect(&oDataAdapter, SIGNAL(ParseError(QString,QString)), &oWindow, SLOT(GPSDataParseError(QString,QString)));

    QObject::connect(&oWindow, SIGNAL(SentenceSend(QString)), this, SLOT(SendMessage(QString)));
}

bool UDPClient::IsValid() const
{
    return UDPBase::IsValid();
}

bool UDPClient::SendMessage(const QString &sMessage)
{
    if (!m_pSocket || sMessage.isEmpty()) return false;

    QByteArray oDatagram(sMessage.toUtf8());
    qint64 iSize = m_pSocket->writeDatagram(oDatagram, m_oAddress, m_uPort);

    return iSize > 0;
}
