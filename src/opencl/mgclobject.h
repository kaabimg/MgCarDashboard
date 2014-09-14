#ifndef MGCLOBJECT_H
#define MGCLOBJECT_H

#include <QObject>
#include <QQmlParserStatus>
#include "../utils/mgglobal.h"


class MgClObject : public QObject,public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(bool valid READ valid NOTIFY validChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
public:
    MgClObject(QObject * parent= 0):QObject(parent)
    {
        m_valid = false;
        m_objectComplete = false;
    }

    QString error() const
    {
        return m_error;
    }

    bool valid()const{return m_valid;}



Q_SIGNALS:
    void errorChanged();
    void validChanged();

protected Q_SLOTS:
    virtual void makeInvalid(const QString & error = "")
    {
        if(!error.isEmpty())
            setError(error);
        setValid(false);
    }
protected:

    virtual void initialize(){}

    virtual void classBegin(){}
    virtual void componentComplete(){
        m_objectComplete = true;
        initialize();
    }


    void clearError()
    {
        setError("");
    }

    bool isObjectComplete()const
    {
        return m_objectComplete;
    }

protected Q_SLOTS:
    void setError(const QString &arg)
    {
        if (m_error != arg) {
            m_error = arg;
            emit errorChanged();
        }
    }

    void setValid(bool v)
    {
        if(m_valid == v)
            return;
        m_valid = v;
        Q_EMIT validChanged();
    }


private:

    bool m_valid;
    bool m_objectComplete;
    QString m_error;

};

#endif // MGCLOBJECT_H
