#include "manipulator.h"

Manipulator::Manipulator(QObject *parent) :
    QObject(parent)
{
    modbusServer = new ModbusServer;
    motorDriver = new MotorDriver;

    modbusServer->startListening();
    connect(modbusServer,SIGNAL(registerChanged(int,quint16)),
            this,SLOT(handleIncomingData(int,quint16)));

}
void Manipulator::handleIncomingData(int index, quint16 data){
    qint16 speed = *reinterpret_cast<quint16*>(&data);
    if(speed>=0){
      motorDriver->setMotor(index, true, (char)speed);
    }
    else{
      motorDriver->setMotor(index, false, (char)(-speed));
    }

}
