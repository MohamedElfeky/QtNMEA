#include "ReceiverWindow.h"
#include <QApplication>
#include "gpsdata_adapter.h"
#include "udp_service.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReceiverWindow oWindow;
    oWindow.show();

    ApplicationMode eMode = ApplicationMode::SERVER;
    UDPService oServce;
    for(int i = 0; i < argc; i++) {
        if(QString(argv[i]) == "-m") {
            eMode = ApplicationMode::CLIENT;
            qDebug() << "run in client mode";
        }
    }

    oServce.Initialize("127.0.0.1", "1234", eMode);

    GPSDataAdapter oGPSData;
    /* GPS Data signals */
    QObject::connect(&oGPSData, SIGNAL(Changed(GPSDataAdapter)), &oWindow, SLOT(GPSDataChanged(GPSDataAdapter)));
    QObject::connect(&oGPSData, SIGNAL(ParseError(QString,QString)), &oWindow, SLOT(GPSDataParseError(QString,QString)));

    /* Window signals */
//    QObject::connect(&oWindow, SIGNAL(SentenceSend(QString)), &oGPSData, SLOT(ReceiveSentence(QString)));
    switch(eMode) {
    case ApplicationMode::SERVER:
        QObject::connect(&oServce, SIGNAL(MessageReceived(QString)), &oGPSData, SLOT(ReceiveSentence(QString)));
        break;
    case ApplicationMode::CLIENT:
        QObject::connect(&oWindow, SIGNAL(SentenceSend(QString)), &oServce, SLOT(MessageSend(QString)));
        break;
    }

    return a.exec();
}
