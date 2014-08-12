#include "gpsserver.h"

const QString GpsServer::FrameStart = "$";
const QString GpsServer::FrameEnd = "\n";
const QString GpsServer::FrameSeparator = ",";

GpsServer::GpsServer(QObject *parent) :
    QObject(parent)
{
    serialPort = new QextSerialPort("/dev/ttyAMA0");
    serialPort->setBaudRate(BAUD115200);
    serialPort->setFlowControl(FLOW_OFF);
    serialPort->setParity(PAR_NONE);
    serialPort->setDataBits(DATA_8);
    serialPort->setStopBits(STOP_1);
    serialPort->close();
    if (serialPort->open(QIODevice::ReadWrite) == true) {
        qDebug("Port opened GPS");
    }
    else {
        qDebug("Could not open serial port GPS");
    }
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readSerial()));
}

void GpsServer::readSerial()
{

    qDebug()<<"New data incomming";
    static QString data;
    data.append(serialPort->readAll());
    int index1 = data.indexOf(FrameStart, 0);
    int index2 = data.indexOf(FrameEnd, index1);
    if (index1 >= 0 && index2 > index1) {
        QString frame = data.mid(index1, index2-index1);
        data.remove(0, index2);
        index1 = frame.indexOf(FrameSeparator, 0);              /* get time */
        time.hours = frame.mid(index1+1, 2).toInt();
        time.minutes = frame.mid(index1+3, 2).toInt();
        time.seconds = frame.mid(index1+5, 2).toInt();
        time.miliseconds = frame.mid(index1+8, 3).toInt();
        index1 = frame.indexOf(FrameSeparator, index1+1);       /* skip valid */
        index1 = frame.indexOf(FrameSeparator, index1+1);       /* get latitude */
        latitude.degrees = frame.mid(index1+1,2).toInt();
        latitude.minutes = frame.mid(index1+3,2).toInt();
        latitude.seconds = frame.mid(index1+6,4).toInt();       /* Not a seconds! */
        index1 = frame.indexOf(FrameSeparator, index1+1);
        latitude.hemisphere = frame.mid(index1+1, 1).toInt();
        index1 = frame.indexOf(FrameSeparator, index1+1);       /* get longitude */
        longitude.degrees = frame.mid(index1+1,3).toInt();
        longitude.minutes = frame.mid(index1+4,2).toInt();
        longitude.seconds = frame.mid(index1+7,4).toInt();      /* Not a seconds! */
        index1 = frame.indexOf(FrameSeparator, index1+1);
        longitude.hemisphere = frame.mid(index1+1, 1).toInt();
        index1 = frame.indexOf(FrameSeparator, index1+1);
        index2 = frame.indexOf(FrameSeparator, index1+1);
        speed = qRound(frame.mid(index1+1, index2-index1-1).toDouble()*1.852*100);  /* get speed */
        index1 = index2;
        index2 = frame.indexOf(FrameSeparator, index1+1);
        cog = qRound(frame.mid(index1+1, index2-index1-1).toDouble()*100);          /* get cog */
        index1 = index2;
        date.day = frame.mid(index1+1, 2).toInt();
        date.month = frame.mid(index1+3, 2).toInt();
        date.year = frame.mid(index1+5, 2).toInt();
        emit updated();
        qDebug()<<latitude.degrees;
    }
}
