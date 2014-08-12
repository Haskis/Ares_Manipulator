#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include <QObject>
#include "motordriver.h"
#include "modbusserver.h"

class Manipulator : public QObject
{
    Q_OBJECT
public:
    explicit Manipulator(QObject *parent = 0);
    
signals:
    
public slots:
private slots:
    void handleIncomingData(int index, quint16 data);
private:
    MotorDriver *motorDriver;
    ModbusServer *modbusServer;

};

#endif // MANIPULATOR_H
