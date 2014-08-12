#include "manipulator.h"

Manipulator::Manipulator(QObject *parent) :
    QObject(parent)
{
    modbusServer = new ModbusServer;
    motorDriver = new MotorDriver;
    ultraZajebistySerwerGpsByRadek = new GpsServer;

    modbusServer->startListening();
    connect(modbusServer,SIGNAL(registerChanged(int,quint16)),
            this,SLOT(handleIncomingData(int,quint16)));
    connect(ultraZajebistySerwerGpsByRadek, SIGNAL(updated()), this, SLOT(handleGps()));

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

void Manipulator::handleGps()
{
    modbusServer->setRegister(10, ultraZajebistySerwerGpsByRadek->getTime().hours);
    modbusServer->setRegister(11, ultraZajebistySerwerGpsByRadek->getTime().minutes);
    modbusServer->setRegister(12, ultraZajebistySerwerGpsByRadek->getTime().seconds);
    modbusServer->setRegister(13, ultraZajebistySerwerGpsByRadek->getTime().miliseconds);
    modbusServer->setRegister(14, ultraZajebistySerwerGpsByRadek->getLatitude().degrees);
    modbusServer->setRegister(15, ultraZajebistySerwerGpsByRadek->getLatitude().minutes);
    modbusServer->setRegister(16, ultraZajebistySerwerGpsByRadek->getLatitude().seconds); /* Not a seconds! */
    modbusServer->setRegister(17, ultraZajebistySerwerGpsByRadek->getLatitude().hemisphere);
    modbusServer->setRegister(18, ultraZajebistySerwerGpsByRadek->getLongitude().degrees);
    modbusServer->setRegister(19, ultraZajebistySerwerGpsByRadek->getLongitude().minutes);
    modbusServer->setRegister(20, ultraZajebistySerwerGpsByRadek->getLongitude().seconds); /* Not a seconds! */
    modbusServer->setRegister(21, ultraZajebistySerwerGpsByRadek->getLongitude().hemisphere);
    modbusServer->setRegister(22, ultraZajebistySerwerGpsByRadek->getSpeed());
    modbusServer->setRegister(23, ultraZajebistySerwerGpsByRadek->getCog());
    modbusServer->setRegister(24, ultraZajebistySerwerGpsByRadek->getDate().day);
    modbusServer->setRegister(25, ultraZajebistySerwerGpsByRadek->getDate().month);
    modbusServer->setRegister(26, ultraZajebistySerwerGpsByRadek->getDate().year);
}
