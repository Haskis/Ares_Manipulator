#include "motordriver.h"

MotorDriver::MotorDriver(QObject *parent) :
    QObject(parent)
{
    myExtSerialPort= new QextSerialPort("/dev/ttyUSB0");
    myExtSerialPort->setBaudRate(BAUD115200);
    myExtSerialPort->setFlowControl(FLOW_OFF);
    myExtSerialPort->setParity(PAR_NONE);
    myExtSerialPort->setDataBits(DATA_8);
    myExtSerialPort->setStopBits(STOP_1);
    myExtSerialPort->close();
    if (myExtSerialPort->open(QIODevice::ReadWrite) == true){
      qDebug("Serial port opened");
    }
    else{
      qDebug("Could not open serial port");
    }
    for(int i=0;i<8;i++){
      myMotorData.append(char(0));
    }
    sendTimer = new QTimer(this);
    safetyTimer = new QTimer(this);

    safetyTimer->setInterval(500);
    sendTimer->setInterval(50);

    connect(safetyTimer,SIGNAL(timeout()),this,SLOT(safetyTimerFunction()));
    connect(sendTimer,SIGNAL(timeout()),SLOT(sendMotorData()));
}

//Set motor value in internal array, sending over UART every refreshTimer timeout.
void MotorDriver::setMotor(int index, bool forward, char speed)
{
  safetyTimer->stop();
  safetyTimer->start();
  if(index<0 || index>7){
    return;
  }
  if(speed<0 || speed > 100){
    return;
  }
  if(forward == true){
    speed = speed | 0b10000000;  //Ustaw 1 na pierwszym miejscu
  }else{
    speed = speed & 0b01111111;
  }
  myMotorData[index] = speed;
}

void MotorDriver::sendMotorData(){
  myExtSerialPort->write(myMotorData);
}

void MotorDriver::safetyTimerFunction(){
  for(int i=0; i<8; i++)
      myMotorData[i] = char(0);
}
