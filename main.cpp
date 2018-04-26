/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "ReceiverWindow.h"
#include <QApplication>
#include "gpsdata_adapter.h"
#include "udp_interface.h"
#include "configuration.h"

int main(int argc, char *argv[])
{
    Configuration oConfig(argc, argv);
    QApplication a(argc, argv);
    ReceiverWindow oWindow;
    oWindow.show();

    UDPInterfacePtr pUdpService = UDPInterface::CreateInstance(oConfig.GetMode());
    if (!pUdpService) return 1;

    GPSDataAdapter oGPSData;
    pUdpService->Initialize(oConfig.GetAddress(), oConfig.GetPort());
    pUdpService->Bind(oGPSData, oWindow);

    oWindow.SetLabelMode( pUdpService->GetInfo() );
    oWindow.HideSendBlock( oConfig.GetMode() );

    return a.exec();
}
