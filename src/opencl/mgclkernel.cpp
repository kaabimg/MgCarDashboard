#include "mgclkernel.h"
#include "mgclprivate.h"





void MgClKernel::argumentsAppendFunction(QQmlListProperty<MgClMemoryObject> *arguments, MgClMemoryObject *value)
{
    MgClKernel * kernel = qobject_cast< MgClKernel *>(arguments->object);
    kernel->d_ptr->arguments.append(value);
    Q_EMIT kernel->argumentsChanged();
}

void MgClKernel::argumentsClearFunction(QQmlListProperty<MgClMemoryObject> *arguments)
{
    MgClKernel * kernel = qobject_cast< MgClKernel *>(arguments->object);
    if(!kernel->d_ptr->arguments.size())
        return;
    kernel->d_ptr->arguments.clear();
    Q_EMIT kernel->argumentsChanged();
}




/////////////////////////////





MgClKernel::MgClKernel(QObject *parent) :
    MgClObject(parent)
{
    d_ptr = new MgClKernelPrivate;

}


MgClKernel::~MgClKernel()
{
    delete d_ptr;
}

MgClNDRange *MgClKernel::offsetRange() const
{
    return d_ptr->offsetRange;
}

void MgClKernel::setOffsetRange(MgClNDRange * range)
{
    if(d_ptr->offsetRange != range)
    {
        if(d_ptr->offsetRange)
            delete d_ptr->offsetRange ;

        d_ptr->offsetRange = range;
        d_ptr->offsetRange->setParent(this);
        Q_EMIT offsetRangeChanged();
    }
}

MgClNDRange *MgClKernel::globalRange() const
{
    return d_ptr->globalRange;
}

void MgClKernel::setGlobalRange(MgClNDRange * range)
{
    if(d_ptr->globalRange != range)
    {
        if(d_ptr->globalRange)
            delete d_ptr->globalRange ;

        d_ptr->globalRange = range;
        d_ptr->globalRange->setParent(this);
        Q_EMIT globalRangeChanged();
    }
}


MgClNDRange *MgClKernel::localRange() const
{
    return d_ptr->localRange;
}

void MgClKernel::setLocalRange(MgClNDRange * range)
{
    if(d_ptr->localRange != range)
    {
        if(d_ptr->localRange)
            delete d_ptr->localRange ;

        d_ptr->localRange = range;
        d_ptr->localRange->setParent(this);
        Q_EMIT localRangeChanged();
    }
}


MgClEnvironment *MgClKernel::environment() const
{
    return d_ptr->environment;
}

void MgClKernel::setEnvironment(MgClEnvironment * environment)
{
    if(d_ptr->environment != environment)
    {
        d_ptr->environment = environment;
        Q_EMIT environmentChanged();
    }
}



QString MgClKernel::name() const
{
    return d_ptr->name;
}

void MgClKernel::setName(const QString & name)
{
    if(d_ptr->name != name)
    {
        d_ptr->name = name;
        Q_EMIT nameChanged();
    }
}

QQmlListProperty<MgClMemoryObject> MgClKernel::arguments()
{
    return QQmlListProperty<MgClMemoryObject>(this,&d_ptr->arguments,&argumentsAppendFunction,0,0,&argumentsClearFunction);
}


void MgClKernel::tryCreateKernel()
{
    if(environment() && environment()->programBuildStatus() == MgClEnvironment::BuildSucces)
    {
        cl_int error;
        d_ptr->kernel = cl::Kernel (d_ptr->environment->d_ptr->program,qPrintable(name()),&error);
        if(error != CL_SUCCESS)
        {
            makeInvalid();
        }
        else
            setValid(true);
    }
    else
    {
        makeInvalid();
    }
}

cl::NDRange createRange(MgClNDRange * range)
{
    if(range == NULL || range->isNull() || !range->isValid())
        return cl::NullRange;

    switch (range->dimensions()) {
    case 1:
        return cl::NDRange(range->x());
        break;
    case 2:
        return cl::NDRange(range->x(),range->y());
        break;
    case 3:
        return cl::NDRange(range->x(),range->y(),range->z());
        break;
    default:
        break;
    }
    return cl::NullRange;
}



void MgClKernel::run()
{
    if(!environment())
        return;

    if(!localRange())
        return;


    if(!d_ptr->arguments.size())
        return;

    if(!valid())
        return;

    Q_EMIT runStarted();

    cl::KernelFunctor functor = d_ptr->kernel.bind(
                d_ptr->environment->d_ptr->commandQueue,
                createRange(offsetRange()),
                createRange(localRange()),
                createRange(globalRange())
                );

    switch (d_ptr->arguments.size()) {

    case 1:
        functor();
        break;
    case 2:
        functor();
        break;

    case 3:
        functor();
        break;
    case 4:
        functor();
        break;
    case 5:
        functor();
        break;
    case 6:
        functor();
        break;
    case 7:
        functor();
        break;
    case 8:
        functor();
        break;
    case 9:
        functor();
        break;
    case 10:
        functor();
        break;
    case 11:
        functor();
        break;
    case 12:
        functor();
        break;
    case 13:
        functor();
        break;
    case 14:
        functor();
        break;
    case 15:
        functor();
        break;
    default:
        break;
    }


    Q_EMIT runFinished();

}
