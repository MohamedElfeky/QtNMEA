/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef TYPES_H
#define TYPES_H

enum class ApplicationMode
{
    STANDALONE,
    UDP_SERVER,
    UDP_CLIENT,
    COMPORT_READER
};

#endif // TYPES_H
