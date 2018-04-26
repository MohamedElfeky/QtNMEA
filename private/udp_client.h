#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "udp_interface.h"
#include "udp_base.h"

class UDPClient : public UDPInterface, protected UDPBase
{
    Q_OBJECT
public:
    virtual bool Initialize(const QString& sAddress, const QString& sPort) override;
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) override;

public slots:
    bool SendMessage(const QString& sMessage);

protected:
    friend class QSharedPointer<UDPClient>;
    friend class UDPInterface;
    explicit UDPClient(QObject *parent = nullptr);
};

#endif // UDP_CLIENT_H
