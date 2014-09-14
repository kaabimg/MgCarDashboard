#include "mgcarstatistics.h"

MgCarStatistics::MgCarStatistics(QObject *parent) :
    QObject(parent),
    m_car(0)
{
    m_updateTimer.setInterval(100);
    m_updateTimer.setSingleShot(false);
    connect(&m_updateTimer,SIGNAL(timeout()),this,SLOT(update()));
}

void MgCarStatistics::setCar(MgCar *car)
{
    m_car = car;
}

void MgCarStatistics::startUpdate(int interval)
{
    if(m_updateTimer.isActive())
        m_updateTimer.stop();
    m_updateTimer.setInterval(interval);
    m_updateTimer.start();
}

void MgCarStatistics::stopUpdate()
{
    m_updateTimer.stop();
}

MgCar *MgCarStatistics::car() const
{
    return m_car;
}
