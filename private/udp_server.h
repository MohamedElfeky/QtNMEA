#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include "udp_interface.h"
#include "udp_base.h"

class UDPServer : public UDPInterface, protected UDPBase
{
    Q_OBJECT
public:
    virtual bool Initialize(const QString& sAddress, const QString& sPort) override;
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) override;

signals:
    void OnMessageReceived(const QString& sMessage);

private slots:
    void ReadSocket();

protected:
    friend class QSharedPointer<UDPServer>;
    friend class UDPInterface;
    explicit UDPServer(QObject *parent = nullptr);
};

#endif // UDP_SERVER_H
