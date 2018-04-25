#include "gpsdata_adapter.h"
#include "strings.h"

GPSDataAdapter::GPSDataAdapter(QObject *parent) :
    QObject(parent),
    m_pGPSDataImpl(nullptr)
{
}

bool GPSDataAdapter::Parse(const QString &sSentence)
{
    try {
        m_pGPSDataImpl = nmea::GPSDataInterface::Parse(sSentence.toStdString());
        if(!m_pGPSDataImpl) {
            emit ParseError("Unknown sentence type", sSentence);
            return false;
        }

        if(!IsValid()) {
            emit ParseError(GetValidationState(), sSentence);
            return false;
        }

        emit Changed(*this);
        return true;
    } catch(const nmea::BaseException& e) {
        emit ParseError(QString::fromUtf8(e.what()), QString::fromUtf8(e.sentence()));
        return false;
    }
}

nmea::SentenceType GPSDataAdapter::GetType() const
{
    if(!m_pGPSDataImpl) return nmea::SentenceType::UNKNOWN;

    return m_pGPSDataImpl->GetType();
}

bool GPSDataAdapter::IsValid() const
{
    if(!m_pGPSDataImpl) return false;

    return m_pGPSDataImpl->GetValidateState() == nmea::ValidationStatus::OK;
}

QString GPSDataAdapter::GetSentence() const
{
    if(!m_pGPSDataImpl) return "";

    nmea::FString sSentence = m_pGPSDataImpl->GetSentence();
    QString sRet = QString::fromUtf8(sSentence.c_str());

    sRet.replace("\r\n", "\\r\\n");
    return sRet;
}

QTime GPSDataAdapter::GetTime() const
{
    if(!m_pGPSDataImpl) return QTime();

    nmea::GPSTime oTime = m_pGPSDataImpl->GetTime();
    return QTime(oTime.Hours(), oTime.Minutes(), oTime.Seconds(), oTime.Milliseconds());
}

QString GPSDataAdapter::GetLatitude() const
{
    if(!m_pGPSDataImpl) return NA;

    nmea::Latitude oLat = m_pGPSDataImpl->GetLatitude();
    QString sFormat = QString::number(oLat.GetDegrees()) + "° " + QString::number(oLat.GetMinutes()) + "' " + oLat.GetDirectionSymbol();
    return sFormat;
}

QString GPSDataAdapter::GetLongitude() const
{
    if(!m_pGPSDataImpl) return NA;

    nmea::Longitude oLong = m_pGPSDataImpl->GetLongitude();
    QString sFormat = QString::number(oLong.GetDegrees()) + "° " + QString::number(oLong.GetMinutes()) + "' " + oLong.GetDirectionSymbol();
    return sFormat;
}

QString GPSDataAdapter::GetGPSQualityIndicator() const
{
    nmea::GPSQuality eQuality = nmea::GPSQuality::NOT_AVAILABLE;
    if(m_pGPSDataImpl)
        eQuality = m_pGPSDataImpl->GetGPSQualityIndicator();

    switch(eQuality)
    {
    case nmea::GPSQuality::GPS_SPS:
        return "GPS SPS mode";
    case nmea::GPSQuality::GPS_DIFFERENTIAL:
        return "differential GPS, SPS mode";
    case nmea::GPSQuality::GPS_PPS:
        return "GPS PPS mode";
    case nmea::GPSQuality::RTK:
        return "Real Time Kinematic";
    case nmea::GPSQuality::FLOAT_RTK:
        return "Float RTK";
    case nmea::GPSQuality::ESTIMATED:
        return "Estimated mode";
    case nmea::GPSQuality::MANUAL:
        return "Manual input mode";
    case nmea::GPSQuality::SIMULATOR:
        return "Simulator mode";
    case nmea::GPSQuality::NOT_AVAILABLE:
    default:
        return "fix not available or invalid";
    }
}

unsigned short GPSDataAdapter::GetSatellitesNumber() const
{
    if(!m_pGPSDataImpl) return 0;

    return m_pGPSDataImpl->GetSatellitesNumber();
}

float GPSDataAdapter::GetHorizontalDilution() const
{
    if(!m_pGPSDataImpl) return .0f;

    return m_pGPSDataImpl->GetHorizontalDilution();
}

float GPSDataAdapter::GetAntennaAltitude() const
{
    if(!m_pGPSDataImpl) return .0f;

    return m_pGPSDataImpl->GetAntennaAltitude();
}

float GPSDataAdapter::GetGeoidalSeparation() const
{
    if(!m_pGPSDataImpl) return .0f;

    return m_pGPSDataImpl->GetGeoidalSeparation();
}

float GPSDataAdapter::GetDifferentialDataAge() const
{
    if(!m_pGPSDataImpl) return .0f;

    nmea::FDuration uDuration = m_pGPSDataImpl->GetDifferentialDataAge();
    return uDuration.count() / 1000.f;
}

unsigned short GPSDataAdapter::GetDifferentialStationID() const
{
    if(!m_pGPSDataImpl) return 0;

    return m_pGPSDataImpl->GetDifferentialStationID();
}

QString GPSDataAdapter::GetValidationState() const
{
    nmea::ValidationStatus eStatus = nmea::ValidationStatus::UNKNOWN;
    if(m_pGPSDataImpl)
        eStatus = m_pGPSDataImpl->GetValidateState();

    switch(eStatus) {
    case nmea::ValidationStatus::OK:
        return "OK";
    case nmea::ValidationStatus::INCORRECT_LENGTH:
        return "Incorrect sentence length";
    case nmea::ValidationStatus::INCORRECT_BEGIN_SIGN:
        return "First sign should be $";
    case nmea::ValidationStatus::INCORRECT_PREFIX:
        return "Prefix/type should be uppercase string and contains 5 letters";
    case nmea::ValidationStatus::INCORRECT_ENDINGS:
        return "Sentence should be ending with \\r\\n";
    case nmea::ValidationStatus::INCORRECT_CHECKSUM:
        return "Checksum is incorrect";
    case nmea::ValidationStatus::UNKNOWN:
    default:
        return NA;
    }
}

void GPSDataAdapter::ReceiveSentence(const QString &sSentence)
{
    QString sFormatStr = sSentence;
    sFormatStr.replace("\\r\\n", "\r\n");
    Parse(sFormatStr);
}
