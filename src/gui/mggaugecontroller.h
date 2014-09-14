#ifndef MGGAUGECONTROLLER_H
#define MGGAUGECONTROLLER_H

#include <QObject>

class MgGaugeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float minValue READ minValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(float maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(float currentValue READ currentValue WRITE setCurrentValue NOTIFY currentValueChanged)
    Q_PROPERTY(float minAngle READ minAngle WRITE setMinAngle NOTIFY minAngleChanged)
    Q_PROPERTY(float maxAngle READ maxAngle WRITE setMaxAngle NOTIFY maxAngleChanged)
    Q_PROPERTY(float projectedAngle READ projectedAngle NOTIFY projectedAngleChanged)

public:
    explicit MgGaugeController(QObject *parent = 0);

    float minValue() const;
    float maxValue() const;
    float currentValue() const;

    float minAngle() const;
    float maxAngle() const;
    float projectedAngle() const;

Q_SIGNALS:

    void minValueChanged(float arg);
    void maxValueChanged(float arg);
    void currentValueChanged(float arg);
    void minAngleChanged(float arg);
    void maxAngleChanged(float arg);
    void projectedAngleChanged(float arg);

public Q_SLOTS:

    void setMinValue(float arg);
    void setMaxValue(float arg);
    void setCurrentValue(float arg);
    void setMinAngle(float arg);
    void setMaxAngle(float arg);

    float xPosition(float w,float angle,float radius)const;
    float yPosition(float h,float angle,float radius)const;

    float calculateProjectedAngle(float value);


protected:
    void calculateProjectedAngle();
private:
    float m_minValue;
    float m_maxValue;
    float m_currentValue;
    float m_minAngle;
    float m_maxAngle;
        float m_projectedAngle;
};

#endif // MGGAUGECONTROLLER_H
