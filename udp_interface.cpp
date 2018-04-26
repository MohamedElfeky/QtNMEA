/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "udp_interface.h"
#include "private/udp_server.h"
#include "private/udp_client.h"
#include "private/udp_dummy.h"

UDPInterfacePtr UDPInterface::CreateInstance(ApplicationMode eMode)
{
    switch (eMode) {
    case ApplicationMode::STANDALONE:
        return QSharedPointer<UDPDummy>::create();
    case ApplicationMode::CLIENT:
        return QSharedPointer<UDPClient>::create();
    case ApplicationMode::SERVER:
        return QSharedPointer<UDPServer>::create();
    }

    return nullptr;
}
