#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <QObject>
#include "motordriver.h"
#include "modbusserver.h"
#include "gpsserver.h"

class Manipulator : public QObject
{
    Q_OBJECT
public:
    explicit Manipulator(QObject *parent = 0);
    
signals:
    
public slots:
private slots:
    void handleIncomingData(int index, quint16 data);
    void handleGps();
private:
    MotorDriver *motorDriver;
    ModbusServer *modbusServer;
    GpsServer *ultraZajebistySerwerGpsByRadek;
};

#endif // MANIPULATOR_H
