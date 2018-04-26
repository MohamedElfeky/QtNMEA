/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "ReceiverWindow.h"
#include <QApplication>
#include "gpsdata_adapter.h"
#include "udp_interface.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReceiverWindow oWindow;
    oWindow.show();

    ApplicationMode eMode = ApplicationMode::STANDALONE;
    for(int i = 0; i < argc; i++) {
        if(QString(argv[i]) == "-m") {
            eMode = ApplicationMode::CLIENT;
            qDebug() << "run in client mode";
        }
    }

    UDPInterfacePtr pUdpService = UDPInterface::CreateInstance(eMode);
    if (!pUdpService) return 1;

    GPSDataAdapter oGPSData;
    pUdpService->Initialize("127.0.0.1", "1234");
    pUdpService->Bind(oGPSData, oWindow);

    return a.exec();
}
