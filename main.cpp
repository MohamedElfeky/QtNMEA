#include "ReceiverWindow.h"
#include <QApplication>
#include "gpsdata_adapter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReceiverWindow oWindow;
    oWindow.show();

    GPSDataAdapter oGPSData;
    QObject::connect(&oGPSData, SIGNAL(Changed(GPSDataAdapter)), &oWindow, SLOT(GPSDataChanged(GPSDataAdapter)));
    QObject::connect(&oGPSData, SIGNAL(ParseError(QString,QString)), &oWindow, SLOT(GPSDataParseError(QString,QString)));

    QObject::connect(&oWindow, SIGNAL(SentenceSend(QString)), &oGPSData, SLOT(ReceiveSentence(QString)));

    return a.exec();
}
