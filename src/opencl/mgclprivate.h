#ifndef MGCLPRIVATE_H
#define MGCLPRIVATE_H


#include <CL/cl.hpp>
#include <string>
#include <QList>
#include <QDebug>

#include "mgclkernel.h"
#include "mgclenvironment.h"

#include "mgclmemoryobject.h"

struct MgClKernelPrivate {

    MgClKernelPrivate() {
        offsetRange = globalRange = localRange = 0;
        environment = 0;
    }

    QString name;
    MgClNDRange* offsetRange;
    MgClNDRange* globalRange;
    MgClNDRange* localRange;
    MgClEnvironment* environment;
    QList<MgClMemoryObject*> arguments;

    cl::Kernel kernel;

};


struct MgClEnvironmentPrivate {

    MgClEnvironmentPrivate(){

        automaticProgramBuild  = false;
        programBuildStatus = MgClEnvironment::NotBuilt;
    }

    MgClEnvironment::ProgramBuildStatus programBuildStatus;

    QString platformName;
    QString deviceName;
    QString programSourceCode;
    bool automaticProgramBuild;


    cl::Platform platform;
    cl::Device device;
    cl::Context context;
    cl::Program program;
    cl::CommandQueue commandQueue;

};



#endif // MGCLPRIVATE_H
