#include "mgio.h"
#include <QDebug>


MgMessagesManager * MgMessagesManager::m_instance = 0;


MgMessagesManager::MgMessagesManager(QObject * parent):QObject(parent)
{
    if(m_instance == 0)
        m_instance = this;
    else
    {
        qDebug()<<connect(m_instance,SIGNAL(informationMsg(QString)),this,SIGNAL(informationMsg(QString)));
        qDebug()<<connect(m_instance,SIGNAL(warningMsg(QString)),this,SIGNAL(warningMsg(QString)));
        qDebug()<<connect(m_instance,SIGNAL(errorMsg(QString)),this,SIGNAL(errorMsg(QString)));
        qDebug()<<connect(m_instance,SIGNAL(logMsg(QString)),this,SIGNAL(logMsg(QString)));
    }
}


MgMessagesManager * MgMessagesManager::instance()
{
    if(m_instance == 0)
        m_instance = new MgMessagesManager;

    return m_instance;
}


void MgMessagesManager::information(const QString &msg)
{
    if(this == m_instance)
    {
        qDebug()<<"Information : "<<qPrintable(msg);
        Q_EMIT informationMsg(msg);
    }
    else
        m_instance->information(msg);

}

void MgMessagesManager::warning(const QString & msg)
{
    if(this == m_instance)
    {
        qDebug()<<"Warning : "<<qPrintable(msg);
        Q_EMIT warningMsg(msg);
    }
    else
        m_instance->warning(msg);
}
void MgMessagesManager::error(const QString & msg)
{
    if(this == m_instance)
    {
        qDebug()<<"Error : "<<qPrintable(msg);
        Q_EMIT errorMsg(msg);
    }
    else
        m_instance->information(msg);
}
void MgMessagesManager::log(const QString & msg)
{
    if(this == m_instance)
    {
        qDebug()<<"Log : "<<qPrintable(msg);
        Q_EMIT logMsg(msg);
    }
    else
        m_instance->warning(msg);
}

MgMessagesManager * MgMessagesManager::globalMsgManager()const
{
    return m_instance;
}

void MgIO::information(const QString & msg)
{
    MgMessagesManager::instance()->information(msg);
}

void MgIO::warning(const QString & msg)
{
    MgMessagesManager::instance()->warning(msg);
}

void MgIO::error(const QString & msg)
{
    MgMessagesManager::instance()->error(msg);
}

void MgIO::log(const QString & msg)
{
    MgMessagesManager::instance()->log(msg);
}
