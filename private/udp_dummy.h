/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef UDP_DUMMY_H
#define UDP_DUMMY_H

#include "udp_interface.h"

class UDPDummy : public UDPInterface
{
    Q_OBJECT
public:
    inline virtual bool Initialize(const QString& sAddress, const QString& sPort) override;
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) override;
    inline virtual QString GetInfo() const override;
    inline virtual bool IsValid() const override;

protected:
    friend class QSharedPointer<UDPDummy>;
    explicit UDPDummy(QObject *parent = nullptr);
};

// Not needed for dummy layer
bool UDPDummy::Initialize(const QString &sAddress, const QString &sPort)
{
    return true;
}

QString UDPDummy::GetInfo() const
{
    return "Standalone Mode";
}

bool UDPDummy::IsValid() const
{
    return true;
}

#endif // UDP_DUMMY_H
