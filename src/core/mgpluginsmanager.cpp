#include "mgpluginsmanager.h"

#include "../utils/mgio.h"

MgPluginsManager * MgPluginsManager::m_globalInstance = 0;

MgPluginsManager * MgPluginsManager::globalInstance()
{
    if(m_globalInstance == 0)
        m_globalInstance = new MgPluginsManager();


    return m_globalInstance;
}


bool MgPluginsManager::registerPlugin(const QString & type,double version,const QMetaObject & metaObject)
{
    if(m_registeredTypes.contains(type) && m_registeredTypes[type].find(version))
    {
        MgIO::log("Can't re-register plugin of type "+QString(metaObject.className())+":  Plugin type and version already used.");
        return false;
    }

    m_registeredTypes[type].insertPlugin(version,metaObject);
    return true;
}

QObject * MgPluginsManager::createObject(const QString & type,double version)const
{

    if(m_registeredTypes.contains(type) )
    {
        const QMetaObject * mo =  m_registeredTypes[type].find(version);
        if(mo)
            return  mo->newInstance();
    }

    MgIO::log("Can't create plugin of type '"+type+"':  Plugin not found.");
    return 0;
}
