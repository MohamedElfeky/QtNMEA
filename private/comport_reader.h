/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef COMPORT_READER_H
#define COMPORT_READER_H

#include "connection_interface.h"
#include <QSerialPort>

class ComPortReader : public ConnectionInterface
{
    Q_OBJECT
public:
    /*
     * @param sAddress = COM{N}
     * @param sPort is unused
     */
    virtual bool Initialize(const Configuration &oConfig);
    virtual void Bind(const GPSDataAdapter& oDataAdapter, const ReceiverWindow& oWindow);
    inline virtual QString GetInfo() const;
    virtual bool IsValid() const;

signals:
    void OnMessageReaded(const QString& sMessage);

private slots:
    void ReadComPort();

protected:
    friend class QSharedPointer<ComPortReader>;
    explicit ComPortReader(QObject *parent = nullptr);

private:
    QSerialPort m_oSerialPort;
};

QString ComPortReader::GetInfo() const
{
    return "COM Port Mode";
}

#endif // COMPORT_READER_H
