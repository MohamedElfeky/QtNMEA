/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "udp_server.h"
#include "gpsdata_adapter.h"
#include "ReceiverWindow.h"

UDPServer::UDPServer(QObject *parent) :
    UDPInterface(parent),
    UDPBase()
{
}

bool UDPServer::Initialize(const QString &sAddress, const QString &sPort)
{
    if (UDPBase::Connect(sAddress, sPort)) {
        connect(m_pSocket.data(), SIGNAL(readyRead()), this, SLOT(ReadSocket()));
        return true;
    }

    return false;
}

void UDPServer::Bind(const GPSDataAdapter &oDataAdapter, const ReceiverWindow &oWindow)
{
    QObject::connect(&oDataAdapter, SIGNAL(Changed(GPSDataAdapter)), &oWindow, SLOT(GPSDataChanged(GPSDataAdapter)));
    QObject::connect(&oDataAdapter, SIGNAL(ParseError(QString,QString)), &oWindow, SLOT(GPSDataParseError(QString,QString)));

    QObject::connect(this, SIGNAL(OnMessageReceived(QString)), &oDataAdapter, SLOT(ReceiveSentence(QString)));
}

void UDPServer::ReadSocket()
{
    if(!m_pSocket) return;

    QByteArray oDatagram(m_pSocket->pendingDatagramSize(), '\0'); // size by pending datagram
    m_pSocket->readDatagram(oDatagram.data(), oDatagram.size(), &m_oAddress, &m_uPort);

    QString sMessage(oDatagram);
    emit OnMessageReceived(sMessage);
}
