/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "dummy_layer.h"
#include "gpsdata_adapter.h"
#include "ReceiverWindow.h"

void DummyLayer::Bind(const GPSDataAdapter &oDataAdapter, const ReceiverWindow &oWindow)
{
    QObject::connect(&oDataAdapter, SIGNAL(Changed(GPSDataAdapter)), &oWindow, SLOT(GPSDataChanged(GPSDataAdapter)));
    QObject::connect(&oDataAdapter, SIGNAL(ParseError(QString,QString)), &oWindow, SLOT(GPSDataParseError(QString,QString)));

    QObject::connect(&oWindow, SIGNAL(SentenceSend(QString)), &oDataAdapter, SLOT(ReceiveSentence(QString)));
}

DummyLayer::DummyLayer(QObject *parent) :
    ConnectionInterface(parent)
{
}
