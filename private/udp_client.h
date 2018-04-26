/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "udp_interface.h"
#include "udp_base.h"

class UDPClient : public UDPInterface, private UDPBase
{
    Q_OBJECT
public:
    virtual bool Initialize(const QString& sAddress, const QString& sPort) override;
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) override;
    inline virtual QString GetInfo() const override;

public slots:
    bool SendMessage(const QString& sMessage);

protected:
    friend class QSharedPointer<UDPClient>;
    explicit UDPClient(QObject *parent = nullptr);
};

QString UDPClient::GetInfo() const
{
    return "Client Mode";
}

#endif // UDP_CLIENT_H
