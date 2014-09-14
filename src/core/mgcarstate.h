#ifndef MGCARSTATE_H
#define MGCARSTATE_H

#include <QObject>
#include <QHash>
class MgAbstractStateMessagesProvider;
class MgAbstractCanMessagesDecoder;

struct MgCarState {

    MgCarState():
        m_speed(0),
        m_rpmMG1(0),
        m_rpmMG2(0),
        m_rpmICE(0),
        m_batteryVoltage(0),
        m_batteryCurrent(0),
        m_fuelLevel(0),
        m_batteryLevel(0),
        m_consumedFuel(0),
        m_instantaneousFuelConsumption(0),
        m_engineTemperature(0),
        m_externalTemperature(0),
        m_totalKilometers(0),
        m_drivenDistance(0),
        m_driveMode("P"),
        m_cruise(false),
        m_evMode(false){}

    int m_speed;
    int m_rpmMG1;
    int m_rpmMG2;
    int m_rpmICE;
    int m_batteryVoltage;
    int m_batteryCurrent;
    int m_fuelLevel;
    float m_batteryLevel;
    float m_consumedFuel;
    float m_instantaneousFuelConsumption;
    int m_engineTemperature;
    int m_externalTemperature;
    int m_totalKilometers;
    float m_drivenDistance;
    QString m_driveMode;
    bool m_cruise;
    bool m_evMode;

};


class MgDriveStatistics;
class MgBatteryStatistics;

class MgCar : public QObject, private MgCarState
{
    Q_OBJECT


    //plugins
    Q_PROPERTY(QString decoderPlugin READ decoderPlugin WRITE setDecoderPlugin NOTIFY decoderPluginChanged)
    Q_PROPERTY(QString physicalConnectionPlugin READ physicalConnectionPlugin WRITE setPhysicalConnectionPlugin NOTIFY physicalConnectionPluginChanged)

    //state

    Q_PROPERTY(double decoderPluginVersion READ decoderPluginVersion WRITE setDecoderPluginVersion NOTIFY decoderPluginVersionChanged)
    Q_PROPERTY(double physicalConnectionPluginVersion READ physicalConnectionPluginVersion WRITE setPhysicalConnectionPluginVersion NOTIFY physicalConnectionPluginVersionChanged)

    //info
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int rpmMG1 READ rpmMG1 NOTIFY rpmMG1Changed)
    Q_PROPERTY(int rpmMG2 READ rpmMG2 NOTIFY rpmMG2Changed)
    Q_PROPERTY(int rpmICE READ rpmICE NOTIFY rpmICEChanged)
    Q_PROPERTY(int batteryVoltage READ batteryVoltage NOTIFY batteryVoltageChanged)
    Q_PROPERTY(int batteryCurrent READ batteryCurrent NOTIFY batteryCurrentChanged)
    Q_PROPERTY(int fuelLevel READ fuelLevel WRITE setFuelLevel NOTIFY fuelLevelChanged)
    Q_PROPERTY(int batteryLevel READ batteryLevel NOTIFY batteryLevelChanged)
    Q_PROPERTY(int engineTemperature READ engineTemperature NOTIFY engineTemperatureChanged)
    Q_PROPERTY(float consumedFuel READ consumedFuel NOTIFY consumedFuelChanged)
    Q_PROPERTY(float instantaneousFuelConsumption READ instantaneousFuelConsumption NOTIFY instantaneousFuelConsumptionChanged)
    Q_PROPERTY(int externalTemperature READ externalTemperature NOTIFY externalTemperatureChanged)
    Q_PROPERTY(int totalKilometers READ totalKilometers NOTIFY totalKilometersChanged)
    Q_PROPERTY(float drivenDistance READ drivenDistance NOTIFY drivenDistanceChanged)
    Q_PROPERTY(QString driveMode READ driveMode NOTIFY driveModeChanged)
    Q_PROPERTY(bool cruise READ cruise NOTIFY cruiseChanged)
    Q_PROPERTY(bool evMode READ evMode NOTIFY evModeChanged)

    Q_PROPERTY(MgDriveStatistics* driveStatistics READ driveStatistics NOTIFY driveStatisticsChanged)
//    Q_PROPERTY(MgBatteryStatistics* batteryStatistics READ batteryStatistics)

public:

    enum DoorState{Open,Closed};
    enum PoweringMode{Electric,Fuel,Hybrid};
    enum BatteryMode{Neutral,Charging,Powering};

    explicit MgCar(QObject *parent = 0);


    MgDriveStatistics* driveStatistics() const;
    MgBatteryStatistics* batteryStatistics() const;


    QString decoderPlugin()const;
    void setDecoderPlugin(const QString &);

    double decoderPluginVersion()const;
    void setDecoderPluginVersion(double);

    QString physicalConnectionPlugin()const;
    void setPhysicalConnectionPlugin(const QString &);

    double physicalConnectionPluginVersion()const;
    void setPhysicalConnectionPluginVersion(double);

    int speed()const;
    int rpmMG1() const;
    int rpmMG2() const;
    int rpmICE() const;
    int batteryVoltage() const;
    int batteryCurrent() const;
    int fuelLevel() const;
    int batteryLevel() const;
    float consumedFuel() const;
    float instantaneousFuelConsumption() const;
    int engineTemperature() const;
    int externalTemperature() const;
    int totalKilometers() const;
    float drivenDistance() const;
    QString driveMode() const;
    bool cruise() const;
    bool evMode() const;
    void updateState(const MgCarState & other);


Q_SIGNALS:

    void decoderPluginChanged();
    void decoderPluginVersionChanged();
    void physicalConnectionPluginChanged();
    void physicalConnectionPluginVersionChanged();
    void connectedToCanChanged();
    void speedChanged();
    void rpmMG1Changed();
    void rpmMG2Changed();
    void rpmICEChanged();
    void batteryVoltageChanged();
    void batteryCurrentChanged();
    void fuelLevelChanged();
    void batteryLevelChanged();
    void consumedFuelChanged();
    void instantaneousFuelConsumptionChanged();
    void engineTemperatureChanged();
    void externalTemperatureChanged();
    void totalKilometersChanged();
    void drivenDistanceChanged();
    void driveModeChanged();
    void cruiseChanged();
    void evModeChanged();
    void driveStatisticsChanged();




public Q_SLOTS:

    void connectToHardware();
    void disconnectFromHardware();
protected:
    void setSpeed(int s);
    void setRpmMG1(int arg);
    void setRpmMG2(int arg);
    void setRpmICE(int arg);
    void setBatteryVoltage(int arg);
    void setBatteryCurrent(int arg);
    void setFuelLevel(int arg);
    void setInstantaneousFuelConsumption(float arg);
    void setBatteryLevel(int arg);
    void setConsumedFuel(float arg);
    void setEngineTemperature(int arg);
    void setExternalTemperature(int arg);
    void setTotalKilometers(int arg);
    void setDrivenDistance(float arg);
    void setDriveMode(QString arg);
    void setCruise(bool arg);
    void setEvMode(bool arg);


private:

    Q_DISABLE_COPY(MgCar)
    MgAbstractStateMessagesProvider * m_messagesProvider;
    MgAbstractCanMessagesDecoder * m_decoder;
    MgDriveStatistics* m_driveStatistics;
    MgBatteryStatistics* m_batteryStatistics;


    QString m_decoderPlugin;
    QString m_physicalConnectionPlugin;
    double m_decoderPluginVersion;
    double m_physicalConnectionPluginVersion;
    bool m_connectedToCan;

    float m_instantaneousFuelConsumption;
};

#endif // MGCARSTATE_H

