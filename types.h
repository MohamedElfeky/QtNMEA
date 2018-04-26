/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef TYPES_H
#define TYPES_H

enum class ApplicationMode : uint8_t
{
    STANDALONE,
    SERVER,
    CLIENT
};

#endif // TYPES_H
