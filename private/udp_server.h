/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "connection_interface.h"
#include "udp_base.h"

class UDPServer : public ConnectionInterface, private UDPBase
{
    Q_OBJECT
public:
    virtual bool Initialize(const Configuration& oConfig) override;
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) override;
    inline virtual QString GetInfo() const override;
    virtual bool IsValid() const override;

signals:
    // Fired when message readed from socket
    void OnMessageReceived(const QString& sMessage);

private slots:
    // Binded to readyRead signal
    void ReadSocket();

protected:
    friend class QSharedPointer<UDPServer>;
    explicit UDPServer(QObject *parent = nullptr);
};

QString UDPServer::GetInfo() const
{
    return "Server Mode";
}

#endif // UDP_SERVER_H
