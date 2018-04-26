#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <QObject>
#include <QUdpSocket>
#include "types.h"

class UDPService : public QObject
{
    Q_OBJECT
public:
    explicit UDPService(QObject *parent = nullptr);
    bool Initialize(const QString& sAddress, const QString& sPort, ApplicationMode eMode = ApplicationMode::SERVER);
    bool Send(const QString& sMessage);

signals:
    void MessageReceived(const QString& sMessage);

public slots:
    void MessageSend(const QString& sMessage);

protected slots:
    void ReadSocket();

protected:
    bool Connect();

    QSharedPointer<QUdpSocket> m_pSocket;
    QHostAddress m_oAddress;
    quint16 m_uPort;
    ApplicationMode m_eMode;
};

#endif // UDP_SERVER_H
