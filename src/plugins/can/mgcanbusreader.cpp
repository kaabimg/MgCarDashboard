#include "mgcanbusreader.h"


#include <QSerialPortInfo>
#include "../../utils/mgio.h"

#include <QDebug>


#define okMsg char(13)
#define errorMsg char(7)
#define carriageReturn "\r"

MgCanBusReader::MgCanBusReader(QObject *parent) :
    MgAbstractStateMessagesProvider(parent),
    m_usbState(Closed),
    m_canState(Closed),
    m_lastMessageOk(true)
{
    connect(&m_serialPort,SIGNAL(readyRead()),this,SLOT(readData()));

}
MgCanBusReader::~MgCanBusReader()
{
    closeCan();
    closeUsb();
}

bool MgCanBusReader::isUsbConnected()const
{
    return m_usbState == Open;
}
bool MgCanBusReader::isCanConnected()const
{
    return m_canState == Open;
}




bool MgCanBusReader::openUsb()
{
    MgIO::log("Trying to fin canusb usb port");
    if(m_serialPort.isOpen())
        return true;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        MgIO::log("Checking port : "+info.description());
        if(info.description() == "CANUSB")
        {
            m_serialPort.setPort(info);
            if(m_serialPort.open(QSerialPort::ReadWrite))
            {
                m_serialPort.setDataBits(QSerialPort::Data8);
                m_serialPort.setParity(QSerialPort::NoParity);
                m_serialPort.setStopBits(QSerialPort::OneStop);
                m_serialPort.setBaudRate(9600);
                MgIO::log("Connected to CANUSB usb port");
                setUsbState(Open);
                return true;

            }
            else
            {
                MgIO::error("Can't open CANUSB : "+m_serialPort.errorString());
                setUsbState(Closed);
                return false;
            }

        }
    }
    MgIO::error("Can't find CANUSB serial port");
    return false;
}

void MgCanBusReader::closeUsb()
{
    if(m_serialPort.isOpen())
    {
        m_serialPort.close();
        MgIO::log("Disconnecting from CANUSB");
        setUsbState(Closed);
    }
}

bool MgCanBusReader::write(const QByteArray & data)
{
    MgIO::log("Writing '"+data+"'");
    m_serialPort.write(data);
    m_serialPort.write(carriageReturn);
    waitForAck();
    return  m_lastMessageOk;
}

 void MgCanBusReader::waitForAck()
 {

     bool okOrerrorReceived = false;
     QByteArray msg;

     while(!okOrerrorReceived)
     {
        m_serialPort.waitForReadyRead(-1);
        QByteArray data = m_serialPort.readAll();
        for (int i = 0; i < data.size(); ++i)
        {
            if(data.at(i) == okMsg)
            {
                if(!msg.isEmpty())
                {
                    Q_EMIT messageReceived(msg);
                    msg.clear();
                }
                else
                {
                    m_lastMessageOk = true;
                    MgIO::log("Ok received from CANUSB");
                    Q_EMIT okMessageReceived();
                    okOrerrorReceived = true;
                }

            }
            else if(data.at(i) == errorMsg)
            {
                m_lastMessageOk = false;
                MgIO::log("Error message received from CANUSB");
                Q_EMIT errorMessageReceived();
                okOrerrorReceived = true;
            }
            else
                msg += data.at(i) ;
        }
     }
}


void MgCanBusReader::readData()
{
    QByteArray msg;
    QByteArray data = m_serialPort.readAll();

    for (int i = 0; i < data.size(); ++i)
    {
        if(data.at(i) == okMsg)
        {
            if(!msg.isEmpty())
            {
                Q_EMIT messageReceived(msg);
                msg.clear();
            }
            else
            {
                m_lastMessageOk = true;
                MgIO::log("Ok received from CANUSB");
                Q_EMIT okMessageReceived();

            }

        }
        else if(data.at(i) == errorMsg)
        {
            m_lastMessageOk = false;
            MgIO::log("Error message received from CANUSB");
            Q_EMIT errorMessageReceived();
        }
        else
            msg += data.at(i) ;
    }
}


void MgCanBusReader::setUsbState(MgCanBusReader::ConnectionState s)
{
    if(m_usbState != s)
    {
        m_usbState = s;
        Q_EMIT usbStateChanged(s);
    }
}

void  MgCanBusReader::setCanState(ConnectionState s)
{
    if(m_canState != s)
    {
        m_usbState = s;
        Q_EMIT usbStateChanged(s);
    }
}




///////////////////////////////////////////

// fuction to contron the canusb



bool MgCanBusReader::openCan()
{
    if(m_serialPort.isOpen())
    {
        return write("O");
    }
    return false;//TODO
}

void MgCanBusReader::closeCan()
{
    if(m_serialPort.isOpen())
    {
        write("C");
    }
}


// hexa values
void MgCanBusReader::setIdsFilter(const QList<QByteArray> & ids)
{
    if(m_serialPort.isOpen())
    {
        foreach (const QByteArray & id, ids)
        {
            //TODO
            Q_UNUSED(id)
        }
    }
}

bool MgCanBusReader::setCanBitRate(MgCanBusReader::CanBitRate rate)
{
    if(!m_serialPort.isOpen())
    {
        MgIO::error("Can't set bit rate : USB port not open");
        return false;
    }
    switch (rate)
    {
    case Bit10:
         return write("S0");
        break;
    case Bit20:
         return write("S1");
        break;
    case Bit50:
         return write("S2");
        break;
    case Bit100:
         return write("S3");
        break;
    case Bit125:
         return write("S4");
        break;
    case Bit250:
         return write("S5");
        break;
    case Bit500:
         return write("S6");
        break;
    case Bit800:
         return write("S7");
        break;
    case Bit1000:
         return write("S8");
        break;
    default:
        break;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////


void MgCanBusReader::connectToHardware()
{
    m_connectionTimer.setInterval(1000);
    m_connectionTimer.setSingleShot(false);
    connect(&m_connectionTimer,SIGNAL(timeout()),this,SLOT(tryToConnectToCan()));
}


void MgCanBusReader::tryToConnectToCan()
{
    MgIO::log("Trying to connect to the can bus through canusb");
    if(openUsb())
    {
        m_connectionTimer.stop();
        if(!setCanBitRate(MgCanBusReader::Bit1000))
            return;
        bool ok =openCan();
        setConnectionState(ok ? Open : Closed);
    }

}

void MgCanBusReader::disconnectFromHardware()
{
    MgIO::log("Disconnecting from the can bus and closing canusb usb port");
    closeCan();
    closeUsb();
    setConnectionState(Closed);
}
