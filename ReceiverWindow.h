#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H

#include <QMainWindow>
#include "gpsdata_adapter.h"

namespace Ui {
class ReceiverWindow;
}

class ReceiverWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReceiverWindow(QWidget *parent = 0);
    ~ReceiverWindow();

signals:
    void SentenceSend(const QString& sSentence);

public slots:
    void GPSDataChanged(const GPSDataAdapter& oData);
    void GPSDataParseError(const QString& sWhat, const QString& sSentence);

private slots:
    void on_btnSend_pressed();

private:
    void ClearDataLabels();

    Ui::ReceiverWindow *ui;
};

#endif // RECEIVERWINDOW_H
