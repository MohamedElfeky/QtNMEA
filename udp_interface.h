/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef UDP_INTERFACE_H
#define UDP_INTERFACE_H

#include <QObject>
#include "types.h"

class GPSDataAdapter;
class ReceiverWindow;
class QString;

class UDPInterface;
typedef QSharedPointer<UDPInterface> UDPInterfacePtr;

/*
 * UDP interface
 * Class provides layer to connect GPSDataAdapter with Window via UDP or Direct connections
 */
class UDPInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~UDPInterface() {}
    // Select instance by mode
    static UDPInterfacePtr CreateInstance(ApplicationMode eMode = ApplicationMode::STANDALONE);
    // Initialize parameters and connect if needed
    virtual bool Initialize(const QString& sAddress, const QString& sPort) = 0;
    // Bind signals/slots
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) = 0;
    // Info string, just for visualization
    virtual QString GetInfo() const = 0;
    // Ready or not
    virtual bool IsValid() const = 0;

protected:
    explicit UDPInterface(QObject *parent = nullptr) : QObject(parent) {}
};

#endif // UDP_INTERFACE_H
