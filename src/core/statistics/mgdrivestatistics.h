#ifndef MGDRIVESTATISTICS_H
#define MGDRIVESTATISTICS_H

#include "mgcarstatistics.h"

class MgDriveStatistics : public MgCarStatistics
{
    Q_OBJECT
    Q_PROPERTY(double meanSpeed READ meanSpeed  NOTIFY meanSpeedChanged)
    Q_PROPERTY(double meanFuelConsumption READ meanFuelConsumption NOTIFY meanFuelConsumptionChanged)
public:
    MgDriveStatistics(QObject * parent=0);

    float meanSpeed() const;
    float meanFuelConsumption() const;

    void reset();

protected Q_SLOTS:

    void setMeanSpeed(double arg);
    void setMeanFuelConsumption(double arg);
    void update();


Q_SIGNALS:

    void meanSpeedChanged();
    void meanFuelConsumptionChanged();
private:

    MgMeanCalculator m_speed;
    double m_meanSpeed;
    double m_meanFuelConsumption;
    float m_lastOdometerValue;
    float m_lastFuelConsumptionValue;

};

#endif // MGDRIVESTATISTICS_H
