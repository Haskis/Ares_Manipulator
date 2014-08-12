#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <QObject>
#include "qextserialport.h"
#include <QByteArray>
#include <QTimer>
class MotorDriver : public QObject
{
    Q_OBJECT
public:
    explicit MotorDriver(QObject *parent = 0);
    
signals:
    
public slots:
  void setMotor(int index, bool forward, char speed); //*< Index from 0 to 8, Speed from 0 to 100
  void sendMotorData();
  void safetyTimerFunction();
private:
  QByteArray myMotorData;
  QTimer *sendTimer;
  QTimer *safetyTimer;
  QextSerialPort *myExtSerialPort;


};

#endif // MOTORDRIVER_H
