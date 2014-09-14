#include "mgprius2canmessagesdecoder.h"

#include "../../core/mgcarstate.h"
#include "../../utils/mgio.h"
#include <QDebug>

#include <stdlib.h>

namespace Prius2Utils {

    enum NodeId {
        Speed = 0x3ca,
        RpmMG1 = 0x3c8,
        RpmMG2 = 0x244,
        RpmICE = 0x526,
        BatteryState = 0x03b,
        BatterySoc = 0x3cb,
        FuelLevel = 0x5a4,
        FuelConsumption = 0x520,
        EngineTemperature = 0x039,
        ExternalTemperature = 0x3CF,
        TotalKilometers = 0x53F,
        Odometer = 0x230,
        DriveMode = 0x540,
        Cruise = 0x5c8,
        EVMode = 0x529
    };

    int hexaToInt(const QByteArray & data)
    {
        return strtol(data.constData(),NULL,16);
    }

    long hexaToLong(const QByteArray & data)
    {
        return strtol(data.constData(),NULL,16);
    }

    uint hexaToUInt(const QByteArray & data)
    {
        return strtoul(data.constData(),NULL,16);
    }

    ulong hexaToULong(const QByteArray & data)
    {
        return strtoul(data.constData(),NULL,16);
    }

    // extract bytes from hexa data in string form
    // 1byte == 2 char
    QByteArray extractBytes(const QByteArray & data,int index,int length)
    {
        QByteArray extract;

        extract.resize(length*2);
        for (int i = 0; i < length*2; ++i) {
            extract[i] = data[index*2+i];
        }
        return extract;
    }

    int speed(const QByteArray & data)
    {
        return hexaToUInt(extractBytes(data,2,1));
    }


    int rpmMG1(const QByteArray & data)
    {
        return hexaToInt(extractBytes(data,4,1));
    }


    int rpmMG2(const QByteArray & data)
    {
        return hexaToInt(extractBytes(data,4,2));

    }

    int rpmICE(const QByteArray & data)
    {
        return (hexaToUInt(extractBytes(data,1,2))*50)/256;
    }



    void batteryState(const QByteArray & data,int & voltage,int & current)
    {
        voltage = hexaToInt(extractBytes(data,2,2));
        // current unit : 10 mA
        current = hexaToInt(extractBytes(data,0,2))/10;
    }

    float batterySoc(const QByteArray & data)
    {
        return (hexaToUInt(extractBytes(data,3,1))*1.0)/2;
    }

    int fuelLevel(const QByteArray & data)
    {
        return  hexaToUInt(extractBytes(data,1,1));

    }

    float fuelConsumption(const QByteArray & data)// in e-6 liter
    {
        return hexaToUInt(extractBytes(data,1,2)) * 0.92185;
    }

    int engineTemperature(const QByteArray & data)
    {
        return hexaToUInt(extractBytes(data,0,1));
    }

    int externalTemperature(const QByteArray & data)
    {
        return hexaToUInt(extractBytes(data,1,1));
    }

    int totalKilometers(const QByteArray & data)
    {
        return hexaToUInt(extractBytes(data,1,3));
    }
    float odometer(const QByteArray & data)
    {
        return hexaToUInt(extractBytes(data,0,2)) *  1.0106;
    }

    QString driveMode(const QByteArray & data)
    {
        int value = hexaToUInt(extractBytes(data,1,1));
        switch (value) {
            case 0:   return "B";
            case 16:  return "D";
            case 32:  return "N";
            case 64:  return "R";
            case 128: return "P";
            default: return "P";
        }
        return "UNKNOWN";
    }

    bool cruise(const QByteArray & data)
    {
        return hexaToUInt(extractBytes(data,2,1));
    }
    bool evMode(const QByteArray & data)
    {
        if(data.size()>=10)
            return hexaToUInt(extractBytes(data,4,1)) == 0x40;
        return false;
    }

}


struct MgCarStatePrius2 : MgCarState {
    MgCarStatePrius2():
        lastOdometerValue(0),
        cumulatedOdometerValue(0)
    {}

    int lastOdometerValue,cumulatedOdometerValue;
};



MgPrius2CanMessagesDecoder::MgPrius2CanMessagesDecoder(QObject * parent):
    MgAbstractCanMessagesDecoder(parent)
{
    m_carState = new MgCarStatePrius2;
    m_updateTimer.setInterval(100);
    connect(&m_updateTimer,SIGNAL(timeout()),this,SLOT(updateCarState()));
    m_updateTimer.start();
}

MgPrius2CanMessagesDecoder::~MgPrius2CanMessagesDecoder()
{
    delete m_carState;
}

QList<QByteArray> MgPrius2CanMessagesDecoder::supportedNodes() const
{
    QList<QByteArray> nodes;
    return nodes;
}

void MgPrius2CanMessagesDecoder::updateCarState()
{
    car()->updateState(*m_carState);
}

void MgPrius2CanMessagesDecoder::decodeMessage(const QByteArray & message)
{

    if(!message.startsWith('t'))//not can message
        return;


    QByteArray sender(3,Qt::Uninitialized);
    QByteArray data;
    int dataBeginIndex =  5;

    sender[0] = message[1];
    sender[1] = message[2];
    sender[2] = message[3];

    data.resize(message.size()-dataBeginIndex);

    for(int i=dataBeginIndex;i<message.size();++i)
    {
        data[i-dataBeginIndex] = message[i];
    }

//    qDebug()<<"Message"<<sender<<data;


    switch (Prius2Utils::hexaToUInt(sender)) {
        case Prius2Utils::Speed:
        {
            m_carState->m_speed = Prius2Utils::speed(data);
            break;
        }
        case Prius2Utils::RpmMG2:
        {
            int value = Prius2Utils::rpmMG2(data);          
            if(value<= 6500)
            {
                m_carState->m_rpmMG2 = value;
                m_carState->m_rpmMG1 = 3.6 * m_carState->m_rpmICE  - 2.6 * m_carState->m_rpmMG2;
            }
            break;
        }
        case Prius2Utils::RpmICE:
        {
            m_carState->m_rpmICE = Prius2Utils::rpmICE(data);
            m_carState->m_rpmMG1 = 3.6 * m_carState->m_rpmICE  - 2.6 * m_carState->m_rpmMG2;
            if(m_carState->m_rpmICE == 0){
                m_carState->m_instantaneousFuelConsumption = 0;

            }
            break;
        }
        case Prius2Utils::BatteryState:
        {
            int voltage,current;

            Prius2Utils::batteryState(data,voltage,current);
            m_carState->m_batteryVoltage = voltage;
            m_carState->m_batteryCurrent = current;
            break;
        }
        case Prius2Utils::BatterySoc:
        {
            m_carState->m_batteryLevel = Prius2Utils::batterySoc(data);
            break;
        }
        case Prius2Utils::FuelLevel:
        {
            int value = Prius2Utils::fuelLevel(data);
            if(value<= 50)
                m_carState->m_fuelLevel = value;
            break;
        }
        case Prius2Utils::FuelConsumption:
        {
            float v =  Prius2Utils::fuelConsumption(data);
            m_carState->m_consumedFuel +=  v;


            if(m_carState->m_speed){
                m_carState->m_instantaneousFuelConsumption = ((v*m_carState->m_rpmICE * 0.0003)/m_carState->m_speed);
            }

            break;
        }
        case Prius2Utils::EngineTemperature:
        {
            m_carState->m_engineTemperature = Prius2Utils::engineTemperature(data);
            break;
        }
        case Prius2Utils::ExternalTemperature:
        {
            m_carState->m_externalTemperature = Prius2Utils::externalTemperature(data);
            break;
        }
        case Prius2Utils::TotalKilometers:
        {
            m_carState->m_totalKilometers = Prius2Utils::totalKilometers(data);
            break;
        }

        case Prius2Utils::Odometer:
        {
            int odo =  Prius2Utils::odometer(data);
            if(odo<m_carState->lastOdometerValue) {
                m_carState->cumulatedOdometerValue +=  m_carState->lastOdometerValue;
            }
            m_carState->lastOdometerValue = odo;
            m_carState->m_drivenDistance  = (m_carState->cumulatedOdometerValue + odo)/100000.;

            break;
        }
        case Prius2Utils::DriveMode:
        {
            m_carState->m_driveMode = Prius2Utils::driveMode(data);
            break;
        }
        case Prius2Utils::Cruise:
        {
            m_carState->m_cruise = Prius2Utils::cruise(data);
            break;
        }
        case Prius2Utils::EVMode:
        {
            m_carState->m_evMode = Prius2Utils::evMode(data);
            break;
        }
        default:
            break;
    }






}
