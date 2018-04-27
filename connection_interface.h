/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef UDP_INTERFACE_H
#define UDP_INTERFACE_H

#include <QObject>
#include "types.h"
#include "configuration.h"

class GPSDataAdapter;
class ReceiverWindow;
class QString;

class ConnectionInterface;
typedef QSharedPointer<ConnectionInterface> ConnectionInterfacePtr;

/*
 * UDP interface
 * Class provides layer to connect GPSDataAdapter with Window via UDP or Direct connections
 */
class ConnectionInterface : public QObject
{
    Q_OBJECT
public:
    virtual ~ConnectionInterface() {}
    // Select instance by mode
    static ConnectionInterfacePtr CreateInstance(ApplicationMode eMode = ApplicationMode::STANDALONE);
    // Initialize parameters and connect if needed
    virtual bool Initialize(const Configuration& oConfig) = 0;
    // Bind signals/slots
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) = 0;
    // Info string, just for visualization
    virtual QString GetInfo() const = 0;
    // Ready or not
    virtual bool IsValid() const = 0;

protected:
    explicit ConnectionInterface(QObject *parent = nullptr) : QObject(parent) {}
};

#endif // UDP_INTERFACE_H
