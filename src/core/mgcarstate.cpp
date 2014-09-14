#include "mgcarstate.h"

#include "mgabstractcanmessagesdecoder.h"
#include "mgabstractstatemessagesprovider.h"
#include "mgpluginsmanager.h"

#include "../utils/mgio.h"

#include "statistics/mgbatterystatistics.h"
#include "statistics/mgdrivestatistics.h"
#include <QDebug>

MgCar::MgCar(QObject *parent) :
    QObject(parent),
    m_messagesProvider(0),
    m_decoder(0),
    m_decoderPluginVersion(0),
    m_physicalConnectionPluginVersion(0),
    m_connectedToCan(false)
{
    m_driveStatistics = new MgDriveStatistics(this);
    m_driveStatistics->setCar(this);
    m_driveStatistics->startUpdate(100);

}




//////////////////////////////////////////////////////////////////////



QString MgCar::decoderPlugin()const
{
    return m_decoderPlugin;
}
void MgCar::setDecoderPlugin(const QString & value)
{
    if(m_decoderPlugin != value)
    {
        m_decoderPlugin = value;
        Q_EMIT decoderPluginChanged();
    }
}

double MgCar::decoderPluginVersion()const
{
    return m_decoderPluginVersion;
}
void MgCar::setDecoderPluginVersion(double value)
{
    if(m_decoderPluginVersion != value)
    {
        m_decoderPluginVersion= value;
        Q_EMIT decoderPluginVersionChanged();
    }
}

QString MgCar::physicalConnectionPlugin()const
{
    return  m_physicalConnectionPlugin;
}
void MgCar::setPhysicalConnectionPlugin(const QString & value)
{
    if(m_physicalConnectionPlugin != value)
    {
        m_physicalConnectionPlugin = value;
        Q_EMIT physicalConnectionPluginChanged();
    }
}

double MgCar::physicalConnectionPluginVersion()const
{
    return  m_physicalConnectionPluginVersion;
}
void MgCar::setPhysicalConnectionPluginVersion(double value)
{
    if(m_physicalConnectionPluginVersion != value)
    {
        m_physicalConnectionPluginVersion = value;
        Q_EMIT physicalConnectionPluginVersionChanged();
    }
}


void MgCar::connectToHardware()
{

    MgIO::log("Trying to connect to the can bus");
    if(m_messagesProvider)
    {
        MgIO::log("Removing old messages provider");
        delete m_messagesProvider;
        m_messagesProvider = 0;
    }
    if(m_decoder)
    {
        MgIO::log("Removing old decoder");
        delete m_decoder;
        m_decoder = 0;
    }

    QObject * plugin = MgPluginsManager::globalInstance()->createObject(m_physicalConnectionPlugin,m_physicalConnectionPluginVersion);

    if(!plugin)
    {
        MgIO::log("Connection to the can bus failed : Physical connection plugin '"+m_physicalConnectionPlugin+"' can't be created");
        return;
    }

    m_messagesProvider = qobject_cast<MgAbstractStateMessagesProvider*>(plugin);
    if(!m_messagesProvider)
    {
        delete plugin;

        MgIO::log("Connection to the can bus failed : Bad type of the physical connection plugin '"+m_physicalConnectionPlugin+"'");
        return;
    }

    m_messagesProvider->setParent(this);


    plugin = MgPluginsManager::globalInstance()->createObject(m_decoderPlugin,m_decoderPluginVersion);


    if(!plugin)
    {
        MgIO::log("Connection to the can bus failed : Messages decoder plugin '"+m_decoderPlugin+"' can't be created");
        return;
    }

    m_decoder = qobject_cast<MgAbstractCanMessagesDecoder*>(plugin);
    if(!m_decoder)
    {
        delete plugin;

        MgIO::log("Connection to the can bus failed : Bad type of the messages decoder plugin '"+m_decoderPlugin+"'");
        return;
    }
    m_decoder->setParent(this);

    m_decoder->init(m_messagesProvider,this);
    m_messagesProvider->connectToHardware();
}

void MgCar::disconnectFromHardware()
{
    if(m_messagesProvider)
    {
        m_messagesProvider->disconnectFromHardware();

    }
}



///////////////////////////////////////////////////////


int MgCar::speed() const
{
    return m_speed;
}


int MgCar::rpmMG1() const
{
    return m_rpmMG1;
}

int MgCar::rpmMG2() const
{
    return m_rpmMG2;
}

int MgCar::rpmICE() const
{
    return m_rpmICE;
}

int MgCar::batteryVoltage() const
{
    return m_batteryVoltage;
}

int MgCar::batteryCurrent() const
{
    return m_batteryCurrent;
}

int MgCar::fuelLevel() const
{
    return m_fuelLevel;
}

int MgCar::batteryLevel() const
{
    return m_batteryLevel;
}


float MgCar::consumedFuel() const
{
    return m_consumedFuel;
}

float MgCar::instantaneousFuelConsumption() const
{
    return m_instantaneousFuelConsumption;
}


int MgCar::engineTemperature() const
{
    return m_engineTemperature;
}

int MgCar::externalTemperature() const
{
    return m_externalTemperature;
}

int MgCar::totalKilometers() const
{
    return m_totalKilometers;
}

float MgCar::drivenDistance() const
{
    return m_drivenDistance;
}

QString MgCar::driveMode() const
{
    return m_driveMode;
}

bool MgCar::cruise() const
{
    return m_cruise;
}

bool MgCar::evMode() const
{
    return m_evMode;
}



void MgCar::setSpeed(int arg)
{
    if (m_speed != arg)
    {
        m_speed = arg;
        Q_EMIT speedChanged();
    }
}

void MgCar::setRpmMG1(int arg)
{
    if (m_rpmMG1 != arg) {
        m_rpmMG1 = arg;
        Q_EMIT rpmMG1Changed();
    }
}

void MgCar::setRpmMG2(int arg)
{
    if (m_rpmMG2 != arg ) {
        m_rpmMG2 = arg;
        Q_EMIT rpmMG2Changed();
    }
}

void MgCar::setRpmICE(int arg)
{
    if (m_rpmICE != arg) {
        m_rpmICE = arg;
        Q_EMIT rpmICEChanged();
    }
}

void MgCar::setBatteryVoltage(int arg)
{
    if (m_batteryVoltage != arg) {        
        m_batteryVoltage = arg;
        Q_EMIT batteryVoltageChanged();
    }
}

void MgCar::setBatteryCurrent(int arg)
{
    if (m_batteryCurrent != arg) {
        m_batteryCurrent = arg;
        Q_EMIT batteryCurrentChanged();
    }
}

void MgCar::setFuelLevel(int arg)
{
    if (m_fuelLevel != arg ) {
        m_fuelLevel = arg;
        Q_EMIT fuelLevelChanged();
    }
}

void MgCar::setInstantaneousFuelConsumption(float arg)
{
    if (m_instantaneousFuelConsumption != arg) {
        m_instantaneousFuelConsumption = arg;
        Q_EMIT instantaneousFuelConsumptionChanged();
    }
}

void MgCar::setBatteryLevel(int arg)
{
    if (m_batteryLevel != arg) {
        m_batteryLevel = arg;
        Q_EMIT batteryLevelChanged();
    }
}



void MgCar::setConsumedFuel(float arg)
{
    if (m_consumedFuel != arg) {
        m_consumedFuel = arg;
        Q_EMIT consumedFuelChanged();
    }
}

void MgCar::setEngineTemperature(int arg)
{
    if (m_engineTemperature != arg) {
        m_engineTemperature = arg;
        Q_EMIT engineTemperatureChanged();
    }
}

void MgCar::setExternalTemperature(int arg)
{
    if (m_externalTemperature != arg) {
        m_externalTemperature = arg;
        Q_EMIT externalTemperatureChanged();
    }
}

void MgCar::setTotalKilometers(int arg)
{
    if (m_totalKilometers != arg) {
        m_totalKilometers = arg;
        Q_EMIT totalKilometersChanged();
    }
}

void MgCar::setDrivenDistance(float arg)
{
    if (m_drivenDistance != arg) {
        m_drivenDistance = arg;
        Q_EMIT drivenDistanceChanged();
    }
}

void MgCar::setDriveMode(QString arg)
{
    if (m_driveMode != arg) {
        m_driveMode = arg;
        Q_EMIT driveModeChanged();
    }
}

void MgCar::setCruise(bool arg)
{
    if (m_cruise != arg) {
        m_cruise = arg;
        Q_EMIT cruiseChanged();
    }
}

void MgCar::setEvMode(bool arg)
{
    if (m_evMode != arg) {
        m_evMode = arg;
        Q_EMIT evModeChanged();
    }
}

MgDriveStatistics *MgCar::driveStatistics() const
{
    return m_driveStatistics;
}

MgBatteryStatistics *MgCar::batteryStatistics() const
{
    return m_batteryStatistics;
}


void MgCar::updateState(const MgCarState &other)
{
    setSpeed(other.m_speed);
    setRpmMG1(other.m_rpmMG1);
    setRpmMG2(other.m_rpmMG2);
    setRpmICE(other.m_rpmICE);
    setBatteryVoltage(other.m_batteryVoltage);
    setBatteryCurrent(other.m_batteryCurrent);
    setFuelLevel(other.m_fuelLevel);
    setBatteryLevel(other.m_batteryLevel);
    setConsumedFuel(other.m_consumedFuel);
    setInstantaneousFuelConsumption(other.m_instantaneousFuelConsumption);
    setEngineTemperature(other.m_engineTemperature);
    setEngineTemperature(other.m_externalTemperature);
    setTotalKilometers(other.m_totalKilometers);
    setDrivenDistance(other.m_drivenDistance);
    setDriveMode(other.m_driveMode);
    setCruise(other.m_cruise);
    setEvMode(other.m_evMode);
}


