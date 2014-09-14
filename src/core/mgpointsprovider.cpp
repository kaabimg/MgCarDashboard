#include "mgpointsprovider.h"
#include <QMetaProperty>
#include <QDebug>
MgPointsProvider::MgPointsProvider(QObject * parent):
    QObject(parent),
    m_source(NULL),
    m_active(true),
    m_propertyValid(false),
    m_initialized(false),
    m_mean(0),
    m_totalPoints(0)
{
    m_updateTimer.setInterval(100);
    connect(&m_updateTimer,SIGNAL(timeout()),SLOT(updateValue()));
}


QObject *MgPointsProvider::source() const
{
    return m_source;
}

QByteArray MgPointsProvider::targetProperty() const
{
    return m_targetProperty;
}

int MgPointsProvider::period() const
{
    return m_updateTimer.interval();
}

bool MgPointsProvider::active() const
{
    return m_active;
}


void MgPointsProvider::setSource(QObject *arg)
{
    if (m_source != arg) {
        m_source = arg;
        Q_EMIT sourceChanged(arg);
    }
}

void MgPointsProvider::setTargetProperty(const QByteArray & arg)
{
    if (m_targetProperty != arg) {
        m_targetProperty = arg;
        Q_EMIT targetPropertyChanged(arg);
    }
}

void MgPointsProvider::setPeriod(int arg)
{
    if (m_updateTimer.interval() != arg) {
        m_updateTimer.setInterval(arg);
        Q_EMIT periodChanged(arg);
    }
}

void MgPointsProvider::setActive(bool arg)
{
    if (m_active != arg) {
        m_active = arg;
        Q_EMIT activeChanged(arg);
    }
}

void MgPointsProvider::init()
{

    if(m_updateTimer.isActive())
    {
        m_updateTimer.stop();
    }

    if(!m_initialized || !m_source || m_targetProperty.isEmpty())
    {
        m_propertyValid = false;
        return;
    }


    const QMetaObject * metaObject= m_source->metaObject();

    m_propertyValid = false;

    for(int i = 0;i<metaObject->propertyCount();++i)
    {
        m_property = metaObject->property(i);
        if(m_targetProperty == m_property.name())
        {
            m_propertyValid = true;
            break;
        }
    }
}

void MgPointsProvider::componentComplete()
{
    m_initialized = true;
    init();
}

float MgPointsProvider::mean() const
{
    return m_mean;
}



void MgPointsProvider::setMean(float v)
{
    if(v != m_mean)
    {
        m_mean = v;
        Q_EMIT meanChanged(v);
    }
}

void MgPointsProvider::updateValue()
{
    addPoint(m_elapsedTimer.elapsed(),m_property.read(m_source).toFloat());
}


void MgPointsProvider::resetStatistics()
{
    m_totalPoints = 0;
    setMean(0);
}

void MgPointsProvider::start()
{
    if(m_propertyValid && m_active && !m_updateTimer.isActive())
    {
        m_elapsedTimer.start();
        m_updateTimer.start();
    }
}

void MgPointsProvider::stop()
{
    m_updateTimer.stop();
}



void MgPointsProvider::addPoint(float time, float value)
{
    setMean(m_mean*(m_totalPoints*1./(m_totalPoints+1)) + value/(m_totalPoints+1));
    ++m_totalPoints;
    Q_EMIT newPoint(time,value);

}


