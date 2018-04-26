/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#ifndef GPSDATA_ADAPTER_H
#define GPSDATA_ADAPTER_H

#include <QObject>
#include <QString>
#include <QTime>
#include <nmea.h>

/*
 * Bridge to native GPSData implementation nmea-cpp library
 */
class GPSDataAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GPSDataAdapter(QObject *parent = nullptr);

    // Parse raw sentence
    bool Parse(const QString& sSentence);
    // Sentence type, i.e. GPGGA
    nmea::SentenceType GetType() const;
    // Check to Valid sentence
    bool IsValid() const;
    // Get original sentence
    QString GetSentence() const;

    QTime GetTime() const;
    QString GetLatitude() const;
    QString GetLongitude() const;
    QString GetGPSQualityIndicator() const;
    unsigned short GetSatellitesNumber() const;
    float GetHorizontalDilution() const;
    float GetAntennaAltitude() const;
    float GetGeoidalSeparation() const;
    float GetDifferentialDataAge() const;
    unsigned short GetDifferentialStationID() const;
    // Validation state, i.e. Checksum error
    QString GetValidationState() const;

signals:
    // Fired when parse is OK
    void Changed(const GPSDataAdapter& oData);
    // Fired when found any error on parse
    void ParseError(const QString& sWhat, const QString& sSentence);

public slots:
    // receive sentence form outer
    void ReceiveSentence(const QString& sSentence);

private:
    nmea::GPSDataPtr m_pGPSDataImpl; // native implementation
};

#endif // GPSDATA_ADAPTER_H
