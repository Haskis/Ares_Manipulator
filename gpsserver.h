#ifndef GPSSERVER_H
#define GPSSERVER_H

#include <QObject>
#include <qextserialport.h>
#include <QString>
#include <QDebug>

struct tTIME
{
    quint16 hours;
    quint16 minutes;
    quint16 seconds;
    quint16 miliseconds;
};

struct tDATE
{
    quint16 day;
    quint16 month;
    quint16 year;
};

struct tCOORDINATE
{
    quint16 degrees;
    quint16 minutes;
    quint16 seconds;
    quint16 hemisphere;
};

class GpsServer : public QObject
{
    Q_OBJECT
public:
    explicit GpsServer(QObject *parent = 0);
    tTIME getTime() { return time; }
    tDATE getDate() { return date; }
    tCOORDINATE getLatitude() { return latitude; }
    tCOORDINATE getLongitude() { return longitude; }
    quint16 getSpeed() { return speed; }
    quint16 getCog() { return cog; }
signals:
    void updated();

public slots:

private slots:
    void readSerial();
private:
    QextSerialPort *serialPort;
    tTIME time;
    tCOORDINATE latitude;
    tCOORDINATE longitude;
    quint16 speed;
    quint16 cog;
    tDATE date;
    static const QString FrameStart;
    static const QString FrameEnd;
    static const QString FrameSeparator;
};

#endif // GPSSERVER_H
