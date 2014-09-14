#ifndef MGCLENVIRONMENT_H
#define MGCLENVIRONMENT_H

#include <QStringList>
#include "mgclobject.h"

class MgClKernel;
class MgClEnvironmentPrivate;


#define DEFAULT_PLATFORM "default platform"
#define DEFAULT_GPU "default gpu"
#define DEFAULT_CPU "default cpu"
#define DEFAULT_ACCELERATOR "default accelerator"


class MgClEnvironment : public MgClObject
{
    Q_OBJECT


    Q_PROPERTY(QStringList allPlatformsNames READ allPlatformsNames)
    Q_PROPERTY(QStringList allDevicesNames READ allDevicesNames)
    Q_PROPERTY(QStringList gpuDevicesNames READ gpuDevicesNames)
    Q_PROPERTY(QStringList cpuDevicesNames READ cpuDevicesNames)
    Q_PROPERTY(QStringList acceleratorDevicesNames READ acceleratorDevicesNames)

    Q_PROPERTY(QString platformName READ platformName WRITE setPlatformName NOTIFY platformNameChanged)
    Q_PROPERTY(QString platformPhysicalName READ platformPhysicalName)
    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName NOTIFY deviceNameChanged)
    Q_PROPERTY(QString devicePhysicalName READ devicePhysicalName)
    Q_PROPERTY(QString deviceType READ deviceType)
    Q_PROPERTY(QString programSourceCode READ programSourceCode WRITE setProgramSourceCode NOTIFY programSourceCodeChanged)
    Q_PROPERTY(bool automaticProgramBuild READ automaticProgramBuild WRITE setAutomaticProgramBuild NOTIFY automaticProgramBuildChanged)
    Q_PROPERTY(ProgramBuildStatus programBuildStatus READ programBuildStatus NOTIFY programBuildStatusChanged)

    Q_ENUMS(ProgramBuildStatus)

public:
    enum ProgramBuildStatus {NotBuilt,BuildError,BuildSucces};
    explicit MgClEnvironment(QObject *parent = 0);
    ~MgClEnvironment();

    QStringList allPlatformsNames()const;
    QStringList allDevicesNames()const;
    QStringList gpuDevicesNames()const;
    QStringList cpuDevicesNames()const;
    QStringList acceleratorDevicesNames()const;


    QString platformName()const;
    void setPlatformName(const QString &);
    QString platformPhysicalName()const;


    QString deviceName()const;
    void setDeviceName(const QString &);
    QString devicePhysicalName()const;
    QString deviceType()const;

    QString programSourceCode()const;
    void setProgramSourceCode(const QString &);

    bool automaticProgramBuild()const;
    void setAutomaticProgramBuild(bool);


    ProgramBuildStatus programBuildStatus() const;

public Q_SLOTS:

    bool create();
    bool buildProgram();



protected:
    void initialize(){create();}
    void setprogramBuildStatus(ProgramBuildStatus arg);

Q_SIGNALS:

    void platformNameChanged();
    void platformPhysicalNameChanged();
    void deviceNameChanged();
    void programSourceCodeChanged();
    void automaticProgramBuildChanged();
    void programBuildStatusChanged();

protected:
    QStringList findDevices(int type)const;

private:
    MG_PRIVATE(MgClEnvironment)
    Q_DISABLE_COPY(MgClEnvironment)
    friend class MgClKernel;


};

#endif // MGCLENVIRONMENT_H
