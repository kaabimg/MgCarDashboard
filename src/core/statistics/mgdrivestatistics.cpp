#include "mgdrivestatistics.h"
#include "../mgcarstate.h"
#include <QDebug>

MgDriveStatistics::MgDriveStatistics(QObject *parent):
    MgCarStatistics(parent),
    m_meanSpeed(0.0),
    m_meanFuelConsumption(0.0),
    m_lastOdometerValue(0.0),
    m_lastFuelConsumptionValue(0.0)
{

}

float MgDriveStatistics::meanSpeed() const
{
    return m_meanSpeed;
}

float MgDriveStatistics::meanFuelConsumption() const
{
    return m_meanFuelConsumption;
}

void MgDriveStatistics::reset()
{
    m_speed.reset();
    m_lastFuelConsumptionValue = car()->consumedFuel();
    m_lastOdometerValue = car()->drivenDistance();
    update();
}

void MgDriveStatistics::update()
{
    static float lastDrivenDistance = 0;
    if(car()->drivenDistance() < lastDrivenDistance)
        qDebug()<<"************  "<<lastDrivenDistance<<car()->drivenDistance();
    lastDrivenDistance = car()->drivenDistance();
    m_speed.update(car()->speed());
    setMeanSpeed(m_speed.mean);
    double value = car()->consumedFuel()-m_lastFuelConsumptionValue;
    double distance = (car()->drivenDistance()-m_lastOdometerValue) * 10000;
    if(distance)
        setMeanFuelConsumption(value/distance);
}

void MgDriveStatistics::setMeanSpeed(double arg)
{
    if (m_meanSpeed != arg) {
        m_meanSpeed = arg;
        Q_EMIT meanSpeedChanged();
    }
}

void MgDriveStatistics::setMeanFuelConsumption(double arg)
{
    if (m_meanFuelConsumption != arg) {
        m_meanFuelConsumption = arg;
        Q_EMIT meanFuelConsumptionChanged();
    }
}

