/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "configuration.h"

Configuration::Configuration() :
    m_eMode(ApplicationMode::STANDALONE),
    m_sAddress(""),
    m_sPort("1234")
{
}

Configuration::Configuration(int argc, char *argv[]) :
    Configuration()
{
    Initialize(argc, argv);
}

void Configuration::Initialize(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++) {
        QString sItem(argv[i]);
        if (sItem == "--server") {
            m_eMode = ApplicationMode::SERVER;
        } else if (sItem == "--client") {
            m_eMode = ApplicationMode::CLIENT;
        } else if (sItem == "--com") {
            m_eMode = ApplicationMode::COMPORT_READER;
        } else if (i < (argc - 1) && sItem.size() == 2 && sItem[0] == '-') {
            switch (sItem[1].toLatin1()) {
            case 'i':
                m_sAddress = argv[i+1];
                break;
            case 'p':
                m_sPort = argv[i+1];
                break;
            }
        }
    }
}
