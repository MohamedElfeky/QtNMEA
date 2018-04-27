/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "connection_interface.h"
#include "private/udp_server.h"
#include "private/udp_client.h"
#include "private/dummy_layer.h"
#include "private/comport_reader.h"

ConnectionInterfacePtr ConnectionInterface::CreateInstance(ApplicationMode eMode)
{
    switch (eMode) {
    case ApplicationMode::STANDALONE:
        return QSharedPointer<DummyLayer>::create();
    case ApplicationMode::UDP_CLIENT:
        return QSharedPointer<UDPClient>::create();
    case ApplicationMode::UDP_SERVER:
        return QSharedPointer<UDPServer>::create();
    case ApplicationMode::COMPORT_READER:
        return QSharedPointer<ComPortReader>::create();
    }

    return nullptr;
}
