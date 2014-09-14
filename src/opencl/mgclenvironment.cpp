#include "mgclenvironment.h"
#include "mgclprivate.h"


MgClEnvironment::MgClEnvironment(QObject *parent) :
    MgClObject(parent)
{
    d_ptr = new MgClEnvironmentPrivate;
}

MgClEnvironment::~MgClEnvironment()
{
    delete d_ptr;
}


QStringList MgClEnvironment::allPlatformsNames()const
{
    QStringList names;
    std::vector<cl::Platform> allPlatforms;
    cl::Platform::get(&allPlatforms);
    for(uint i=0;i<allPlatforms.size();++i)
        names<<allPlatforms[i].getInfo<CL_PLATFORM_NAME>().c_str();

    return names;
}


QStringList MgClEnvironment::findDevices(int type)const
{
    QStringList names;
    std::vector<cl::Device> allDevices;
    d_ptr->platform.getDevices(type, &allDevices);
    for(uint i =0;i<allDevices.size();++i)
    {
        names<<allDevices[i].getInfo<CL_DEVICE_NAME>().c_str();
    }
    return names;

}

QStringList MgClEnvironment::allDevicesNames()const
{
    return findDevices(CL_DEVICE_TYPE_ALL);
}


QStringList MgClEnvironment::cpuDevicesNames()const
{
    return findDevices(CL_DEVICE_TYPE_CPU);
}

QStringList MgClEnvironment::acceleratorDevicesNames() const
{

    return findDevices(CL_DEVICE_TYPE_ACCELERATOR);
}

QStringList MgClEnvironment::gpuDevicesNames()const
{
    return findDevices(CL_DEVICE_TYPE_GPU);
}



QString MgClEnvironment::platformName() const
{
    return d_ptr->platformName;
}

void MgClEnvironment::setPlatformName(const QString & name)
{
    if(d_ptr->platformName != name)
    {
        d_ptr->platformName = name;
        Q_EMIT platformNameChanged();

        if(isObjectComplete())
            create();
    }
}


QString MgClEnvironment::platformPhysicalName()const
{
    return d_ptr->platform.getInfo<CL_PLATFORM_NAME>().c_str();
}

QString MgClEnvironment::deviceName() const
{
    return d_ptr->deviceName;
}


void MgClEnvironment::setDeviceName(const QString & name)
{
    if(d_ptr->deviceName != name)
    {
        d_ptr->deviceName = name;
        Q_EMIT deviceNameChanged();
        if(isObjectComplete())
            create();
    }
}

QString MgClEnvironment::devicePhysicalName()const
{
    return d_ptr->device.getInfo<CL_DEVICE_NAME>().c_str();
}

QString MgClEnvironment::deviceType()const
{
    if(!valid())
        return "undefined";

    switch (d_ptr->device.getInfo<CL_DEVICE_TYPE>()) {
    case CL_DEVICE_TYPE_CPU:
        return "cpu";
        break;

    case CL_DEVICE_TYPE_GPU:
        return "gpu";
        break;
    case CL_DEVICE_TYPE_ACCELERATOR:
        return "accelerator";
        break;
    default:
        break;
    }

    return "undefined";
}

QString MgClEnvironment::programSourceCode() const
{
    return d_ptr->programSourceCode;
}

void MgClEnvironment::setProgramSourceCode(const QString & sCode)
{
    if(d_ptr->programSourceCode != sCode)
    {
        d_ptr->programSourceCode = sCode;
        Q_EMIT programSourceCodeChanged();
        if(isObjectComplete() && valid() &&automaticProgramBuild())
            buildProgram();
    }
}

bool MgClEnvironment::automaticProgramBuild() const
{
    return d_ptr->automaticProgramBuild;
}

void MgClEnvironment::setAutomaticProgramBuild(bool b)
{
    if(d_ptr->automaticProgramBuild != b)
    {
        d_ptr->automaticProgramBuild = b;
        Q_EMIT automaticProgramBuildChanged();
    }
}

MgClEnvironment::ProgramBuildStatus MgClEnvironment::programBuildStatus() const
{
    return d_ptr->programBuildStatus;
}
#include <QQuickItem>
#include <QQuickWindow>
bool MgClEnvironment::create()
{

    QObject *  p = parent();
    while (p) {
        qDebug()<<"--------------------------";
        qDebug()<<p;
        QQuickItem * item = qobject_cast<QQuickItem*>(p);
        if(item)
        {
            qDebug()<<item;
            qDebug()<<item->window();
            if(item->window())
            {
                qDebug()<<item->window()->openglContext();
                qDebug()<<item->window()->renderTarget();
            }
        }


        p = p->parent();

    }

    /************************   platform  ***************************/

    if(platformName().isEmpty())
    {
        makeInvalid();
        setError("Can't initialize patform : Name not set");
        return false;
    }

    std::vector<cl::Platform> allPlatforms;
    cl::Platform::get(&allPlatforms);
    if(allPlatforms.size() == 0)
    {
        makeInvalid("Can't initialize patform : No platforms found");
        return false;
    }

    bool found = false;

    if(platformName()== DEFAULT_PLATFORM)
    {
        d_ptr->platform = allPlatforms[0];
        MgIO::log("Creating default platform '"+platformPhysicalName()+"'");
        found = true;
    }
    else
    {
        for(uint i=0;i<allPlatforms.size();++i)
        {
            if(platformName() == allPlatforms[i].getInfo<CL_PLATFORM_NAME>().c_str())
            {
                d_ptr->platform = allPlatforms[i];
                MgIO::log("Creating platform '"+platformPhysicalName()+"'");
                found = true;
                break;
            }
        }
    }

    if(!found)
    {
        makeInvalid("Can't initialize patform '"+platformName()+"'' : Platform not found");
        return false;
    }


    /************************   device  ***************************/

    if(deviceName().isEmpty())
    {
        makeInvalid("Can't initialize Cl device : Name not initialized");
        return false;
    }

    cl_device_type type;
    if(deviceName() == DEFAULT_GPU)
    {
        type = CL_DEVICE_TYPE_GPU;
    }
    else if(deviceName() == DEFAULT_CPU)
    {
        type = CL_DEVICE_TYPE_CPU;
    }
    else if(deviceName()== DEFAULT_ACCELERATOR)
    {
        type = CL_DEVICE_TYPE_ACCELERATOR;
    }
    else
        type = CL_DEVICE_TYPE_ALL;


    std::vector<cl::Device> allDevices;
    d_ptr->platform.getDevices(type, &allDevices);

    if(allDevices.empty())
    {
        makeInvalid("Can't initialize Cl device : Device not found");
        return false;
    }


    found = false;

    if(type != CL_DEVICE_TYPE_ALL)
    {
        d_ptr->device = allDevices[0];
        MgIO::log("Created Cl device '"+devicePhysicalName()+"'");
        found = true;
    }


    for(uint i =0;i<allDevices.size();++i)
    {
        if(deviceName() == allDevices[i].getInfo<CL_DEVICE_NAME>().c_str())
        {
            d_ptr->device = allDevices[i];
            MgIO::log("Created Cl device '"+devicePhysicalName()+"'");
            found = true;
        }
    }


    if(!found)
    {
        makeInvalid("Can't initialize Cl device : Device not found");
        return false;
    }





    /************************   context  ***************************/


    std::vector<cl::Device> devices;
    devices.push_back(d_ptr->device);
    d_ptr->context  = cl::Context(devices);



    /************************ init ok ******************************/


    d_ptr->commandQueue = cl::CommandQueue(d_ptr->context,d_ptr->device);
    setValid(true);


    /************************   program  ***************************/

    buildProgram();

    return true;
}



bool MgClEnvironment::buildProgram()
{
    cl::Program::Sources sources;

    sources.push_back(std::make_pair(qPrintable(d_ptr->programSourceCode), d_ptr->programSourceCode.size()));
    d_ptr->program = cl::Program(d_ptr->context,sources);

    std::vector<cl::Device> devices;
    devices.push_back(d_ptr->device);

    if( d_ptr->program.build(devices)!=CL_SUCCESS){

        QString errorString = "Failed to build program : \n";
        for (uint i = 0; i <devices.size(); ++i) {
            errorString += "   Error for device ";
            errorString += devices[i].getInfo<CL_DEVICE_NAME>().c_str();
            errorString += " :\n";
            errorString += "   ";
            errorString += d_ptr->program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[i]).c_str();
        }
        setError(errorString);
        setprogramBuildStatus(BuildError);
        return false;
    }
    setprogramBuildStatus(BuildSucces);
    return true;
}

void MgClEnvironment::setprogramBuildStatus(MgClEnvironment::ProgramBuildStatus arg)
{
    d_ptr->programBuildStatus = arg;
    Q_EMIT programBuildStatusChanged();
}


