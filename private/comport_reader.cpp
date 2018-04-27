/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "comport_reader.h"
#include "gpsdata_adapter.h"
#include "ReceiverWindow.h"
#include "utils.h"
#include <QThread>

bool ComPortReader::Initialize(const Configuration &oConfig)
{
    QString sTempAddress(oConfig.GetAddress());
    if (sTempAddress.isEmpty())
        sTempAddress = "COM1";
    if (!Utils::IsComPort(sTempAddress)) return false;

    m_oSerialPort.setPortName(sTempAddress);
    /* Typical configuration */
    m_oSerialPort.setBaudRate(4800, QSerialPort::Input);
    m_oSerialPort.setDataBits(QSerialPort::Data8);
    m_oSerialPort.setParity(QSerialPort::NoParity);
    m_oSerialPort.setStopBits(QSerialPort::OneStop);

    if (!m_oSerialPort.open(QIODevice::ReadOnly)) return false;

    connect(&m_oSerialPort, SIGNAL(readyRead()), this, SLOT(ReadComPort()));
    return true;
}

void ComPortReader::Bind(const GPSDataAdapter &oDataAdapter, const ReceiverWindow &oWindow)
{
    QObject::connect(&oDataAdapter, SIGNAL(Changed(GPSDataAdapter)), &oWindow, SLOT(GPSDataChanged(GPSDataAdapter)));
    QObject::connect(&oDataAdapter, SIGNAL(ParseError(QString,QString)), &oWindow, SLOT(GPSDataParseError(QString,QString)));

    QObject::connect(this, SIGNAL(OnMessageReaded(QString)), &oDataAdapter, SLOT(ReceiveSentence(QString)));
}

bool ComPortReader::IsValid() const
{
    return m_oSerialPort.isOpen();
}

void ComPortReader::ReadComPort()
{
    QByteArray oBytes = m_oSerialPort.readAll();

    if(!oBytes.isEmpty()) {
        QString sMessage(oBytes);
        emit OnMessageReaded(sMessage);
    }
}

ComPortReader::ComPortReader(QObject *parent) :
    ConnectionInterface(parent),
    m_oSerialPort()
{
}
