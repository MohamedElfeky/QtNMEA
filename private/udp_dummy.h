#ifndef UDP_DUMMY_H
#define UDP_DUMMY_H

#include "udp_interface.h"

class UDPDummy : public UDPInterface
{
    Q_OBJECT
public:
    inline virtual bool Initialize(const QString& sAddress, const QString& sPort) override;
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow);

protected:
    friend class QSharedPointer<UDPDummy>;
    friend class UDPInterface;
    explicit UDPDummy(QObject *parent = nullptr);
};

bool UDPDummy::Initialize(const QString &sAddress, const QString &sPort)
{
    return true;
}

#endif // UDP_DUMMY_H
