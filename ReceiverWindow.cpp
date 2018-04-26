/*
 * Qt Wrap of NMEA-CPP library, send/receive sentence
 * @author Vladimir Ziablitskii
 * Copyright 2018, All rights reserved
 */

#include "ReceiverWindow.h"
#include "ui_ReceiverWindow.h"
#include "strings.h"

ReceiverWindow::ReceiverWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReceiverWindow)
{
    ui->setupUi(this);
}

ReceiverWindow::~ReceiverWindow()
{
    delete ui;
}

void ReceiverWindow::GPSDataChanged(const GPSDataAdapter& oData)
{
    ui->labelSentence->setText(oData.GetSentence());
    ui->labelStatus->setText(SUCCESS);
    ui->labelFailure->setText(OK);

    ui->labelTime->setText(oData.GetTime().toString("hh:mm:ss.zzz"));
    ui->labelLatitude->setText(oData.GetLatitude());
    ui->labelLongitude->setText(oData.GetLongitude());
    ui->labelGPSQuality->setText(oData.GetGPSQualityIndicator());
    ui->labelSatellites->setText(QString::number(oData.GetSatellitesNumber()));
    ui->labelHorDilution->setText(QString::number(oData.GetHorizontalDilution()));
    ui->labelAntenna->setText(QString::number(oData.GetAntennaAltitude()) + " " + METER);
    ui->labelGeoidal->setText(QString::number(oData.GetGeoidalSeparation()) + " " + METER);
    ui->labelDataAge->setText(QString::number(oData.GetDifferentialDataAge()));
    ui->labelStation->setText(QString::number(oData.GetDifferentialStationID()));
}

void ReceiverWindow::GPSDataParseError(const QString &sWhat, const QString &sSentence)
{
    ui->labelSentence->setText(sSentence);
    ui->labelStatus->setText(FAILURE);
    ui->labelFailure->setText(sWhat);

    ClearDataLabels();
}

void ReceiverWindow::ClearDataLabels()
{
    ui->labelTime->setText(NA);
    ui->labelLatitude->setText(NA);
    ui->labelLongitude->setText(NA);
    ui->labelGPSQuality->setText(NA);
    ui->labelSatellites->setText(NA);
    ui->labelHorDilution->setText(NA);
    ui->labelAntenna->setText(NA);
    ui->labelGeoidal->setText(NA);
    ui->labelDataAge->setText(NA);
    ui->labelStation->setText(NA);
}

void ReceiverWindow::on_btnSend_pressed()
{
    QString sSendString = ui->editSentence->text();
    if (sSendString.isEmpty()) return;

    emit SentenceSend(sSendString);
}
