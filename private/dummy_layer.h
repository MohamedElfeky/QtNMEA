/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef UDP_DUMMY_H
#define UDP_DUMMY_H

#include "connection_interface.h"

class DummyLayer : public ConnectionInterface
{
    Q_OBJECT
public:
    inline virtual bool Initialize(const Configuration& oConfig) override;
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) override;
    inline virtual QString GetInfo() const override;
    inline virtual bool IsValid() const override;

protected:
    friend class QSharedPointer<DummyLayer>;
    explicit DummyLayer(QObject *parent = nullptr);
};

// Not needed for dummy layer
bool DummyLayer::Initialize(const Configuration &oConfig)
{
    return true;
}

QString DummyLayer::GetInfo() const
{
    return "Standalone Mode";
}

bool DummyLayer::IsValid() const
{
    return true;
}

#endif // UDP_DUMMY_H
