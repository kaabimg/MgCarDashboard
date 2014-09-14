#include "mgusbgpspositionsource.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#define BU_353_S4_MANUFACTURER "Prolific Technology Inc."
MgUsbGpsPositionSource::MgUsbGpsPositionSource(QObject * parent):QNmeaPositionInfoSource(RealTimeMode,parent)
{  
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo & port, ports) {
        if(port.manufacturer() == BU_353_S4_MANUFACTURER)
        {
            m_serialPort = new QSerialPort(port,this);
            connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(readData()));
            m_serialPort->setBaudRate(4800);
            setDevice(m_serialPort);
            startUpdates();
            break;
        }
    }
}




