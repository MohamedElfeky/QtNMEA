#ifndef UDP_INTERFACE_H
#define UDP_INTERFACE_H

#include <QObject>
#include "types.h"

class GPSDataAdapter;
class ReceiverWindow;
class QString;

class UDPInterface;
typedef QSharedPointer<UDPInterface> UDPInterfacePtr;

class UDPInterface : public QObject
{
    Q_OBJECT
public:
    static UDPInterfacePtr CreateInstance(ApplicationMode eMode = ApplicationMode::STANDALONE);
    virtual ~UDPInterface() {}
    virtual bool Initialize(const QString& sAddress, const QString& sPort) = 0;
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow) = 0;

protected:
    explicit UDPInterface(QObject *parent = nullptr) : QObject(parent) {}
};

#endif // UDP_INTERFACE_H
