#ifndef MGCLKERNEL_H
#define MGCLKERNEL_H

#include "mgclobject.h"
#include <QQmlListProperty>

class MgClKernelPrivate;
class MgClMemoryObject;
class MgClNDRange;
class MgClEnvironment;


class MgClKernel : public MgClObject {

    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(MgClNDRange* offsetRange READ offsetRange WRITE setOffsetRange NOTIFY offsetRangeChanged)
    Q_PROPERTY(MgClNDRange* globalRange READ globalRange WRITE setGlobalRange NOTIFY globalRangeChanged)
    Q_PROPERTY(MgClNDRange* localRange READ localRange WRITE setLocalRange NOTIFY localRangeChanged)
    Q_PROPERTY(MgClEnvironment* environment READ environment WRITE setEnvironment NOTIFY environmentChanged)

    Q_PROPERTY(QQmlListProperty<MgClMemoryObject> arguments READ arguments)


public:
    explicit MgClKernel(QObject *parent = 0);
    ~MgClKernel();

    QString name()const;
    void setName(const QString &);

    MgClNDRange* offsetRange()const;
    void setOffsetRange(MgClNDRange* );

    MgClNDRange* globalRange()const;
    void setGlobalRange(MgClNDRange* );


    MgClNDRange* localRange()const;
    void setLocalRange(MgClNDRange* );


    MgClEnvironment *environment()const;
    void setEnvironment(MgClEnvironment* );

    QQmlListProperty<MgClMemoryObject> arguments();


private://arguments list qml bindings function
    static void argumentsAppendFunction(QQmlListProperty<MgClMemoryObject> *arguments, MgClMemoryObject *value);
    static void argumentsClearFunction(QQmlListProperty<MgClMemoryObject> *arguments);



public Q_SLOTS:
    void run();
    void tryCreateKernel();



Q_SIGNALS:
    void offsetRangeChanged();
    void globalRangeChanged();
    void localRangeChanged();
    void environmentChanged();
    void nameChanged();
    void argumentsChanged();
    void runStarted();
    void runFinished();

private:
    Q_DISABLE_COPY(MgClKernel)
    MG_PRIVATE(MgClKernel)
    friend class MgClEnvironment;
};



class MgClNDRange : public QObject {

    Q_OBJECT
    Q_PROPERTY(uint x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(uint y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(uint z READ z WRITE setZ NOTIFY zChanged)
    Q_PROPERTY(uint dimensions READ dimensions)
    Q_PROPERTY(bool isNull READ isNull)
    Q_PROPERTY(bool isValid READ isValid)

public:
    explicit MgClNDRange(QObject *parent=0) : QObject(parent)
    {
        m_x = m_y= m_z = 0;
    }
    uint x() const { return m_x; }
    uint y() const { return m_y; }
    uint z() const { return m_z; }
    bool isNull() const { return m_x== 0 && m_y==0 && m_z ==0; }


    uint dimensions() const
    {
        uint d = 0;
        if(m_x)++d;
        if(m_y)++d;
        if(m_z)++d;
        return d;
    }

    bool isValid() const
    {
        if(!m_x  && (m_y || m_z))
            return false;
        if(!m_y && m_z)
            return false;
        return true;
    }

public Q_SLOTS:

    void setX(uint arg)
    {
        if (m_x != arg) {
            m_x = arg;
            emit xChanged();
        }
    }
    void setY(uint arg)
    {
        if (m_y != arg) {
            m_y = arg;
            emit yChanged();
        }
    }

    void setZ(uint arg)
    {
        if (m_z != arg) {
            m_z = arg;
            emit zChanged();
        }
    }

Q_SIGNALS:
    void xChanged();
    void yChanged();
    void zChanged();


private:
    uint m_x,m_y,m_z;
};


#endif // MGCLKERNEL_H
