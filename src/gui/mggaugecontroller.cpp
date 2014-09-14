#include "mggaugecontroller.h"
#include <math.h>

MgGaugeController::MgGaugeController(QObject *parent) :
    QObject(parent),
    m_minValue(0),
    m_maxValue(100),
    m_currentValue(0),
    m_minAngle(0),
    m_maxAngle(100),
    m_projectedAngle(0)
{
}

float MgGaugeController::minValue() const
{
    return m_minValue;
}

float MgGaugeController::maxValue() const
{
    return m_maxValue;
}

float MgGaugeController::currentValue() const
{
    return m_currentValue;
}

float MgGaugeController::projectedAngle() const
{
    return m_projectedAngle;
}

float MgGaugeController::minAngle() const
{
    return m_minAngle;
}

float MgGaugeController::maxAngle() const
{
    return m_maxAngle;
}

void MgGaugeController::setMinValue(float arg)
{
    if (m_minValue != arg) {
        m_minValue = arg;
        Q_EMIT minValueChanged(arg);
        calculateProjectedAngle();
    }
}

void MgGaugeController::setMaxValue(float arg)
{
    if (m_maxValue != arg) {
        m_maxValue = arg;
        Q_EMIT maxValueChanged(arg);
        calculateProjectedAngle();
    }
}

void MgGaugeController::setCurrentValue(float arg)
{
    if (m_currentValue != arg) {
        m_currentValue = arg;
        Q_EMIT currentValueChanged(arg);             
        calculateProjectedAngle();
    }
}

void MgGaugeController::setMinAngle(float arg)
{
    if (m_minAngle != arg) {
        m_minAngle = arg;
        Q_EMIT minAngleChanged(arg);
        calculateProjectedAngle();
    }
}

void MgGaugeController::setMaxAngle(float arg)
{
    if (m_maxAngle != arg) {
        m_maxAngle = arg;
        Q_EMIT maxAngleChanged(arg);
        calculateProjectedAngle();
    }
}

float MgGaugeController::xPosition(float w, float angle, float radius) const
{
    return w/2 + radius * cos(angle);
}

float MgGaugeController::yPosition(float h, float angle, float radius) const
{
    return h/2 - radius * sin(angle);
}

float MgGaugeController::calculateProjectedAngle(float value)
{
    if(value<m_minValue)
        value= m_minValue;
    if(value>m_maxValue)
        value = m_maxValue;
    float v = (value - m_minValue)/(m_maxValue-m_minValue);
    return m_minAngle + v *(m_maxAngle-m_minAngle);
}

void MgGaugeController::calculateProjectedAngle()
{
    float value = calculateProjectedAngle(m_currentValue);
    if (m_projectedAngle != value) {
        m_projectedAngle = value;
        Q_EMIT projectedAngleChanged(value);
    }
}
