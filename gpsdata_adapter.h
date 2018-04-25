#ifndef GPSDATA_ADAPTER_H
#define GPSDATA_ADAPTER_H

#include <QObject>
#include <QString>
#include <QTime>
#include <nmea.h>

class GPSDataAdapter : public QObject
{
    Q_OBJECT
public:
    explicit GPSDataAdapter(QObject *parent = nullptr);

    bool Parse(const QString& sSentence);
    nmea::SentenceType GetType() const;
    bool IsValid() const;

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
    QString GetValidationState() const;

signals:
    void Changed(const GPSDataAdapter& oData);
    void ParseError(const QString& sWhat, const QString& sSentence);

public slots:
    void ReceiveSentence(const QString& sSentence);

private:
    nmea::GPSDataPtr m_pGPSDataImpl;
};

#endif // GPSDATA_ADAPTER_H
