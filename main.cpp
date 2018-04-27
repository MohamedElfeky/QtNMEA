/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "ReceiverWindow.h"
#include <QApplication>
#include "gpsdata_adapter.h"
#include "connection_interface.h"
#include "configuration.h"

int main(int argc, char *argv[])
{
    Configuration oConfig(argc, argv);
    QApplication a(argc, argv);
    ReceiverWindow oWindow;
    oWindow.show();

    ConnectionInterfacePtr pService = ConnectionInterface::CreateInstance(oConfig.GetMode());
    if (!pService) return 1; // no connection created, should not be ever fired

    GPSDataAdapter oGPSData; // input data handler
    if (!pService->Initialize(oConfig)) return 2; // incorrect input parameters
    pService->Bind(oGPSData, oWindow);

    oWindow.SetLabelMode( pService->GetInfo() );
    oWindow.HideSendBlock( oConfig.GetMode() );

    return a.exec();
}
