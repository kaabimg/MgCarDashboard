#ifndef MGPLUGINSMANAGER_H
#define MGPLUGINSMANAGER_H
#include <QMetaType>
#include <QHash>



struct MgPluginMetaObject {
    QMetaObject metaObject;
    double pluginVersion;
};

struct MgPluginProvider {


    const QMetaObject * find(double v)const
    {
        foreach (const MgPluginMetaObject & p, plugins) {
            if(p.pluginVersion == v)
                return &p.metaObject;
        }
        return 0;
    }

    void insertPlugin(double v,const QMetaObject & mo)
    {
        MgPluginMetaObject p;
        p.pluginVersion = v;
        p.metaObject = mo;
        plugins<<p;
    }

    QList<MgPluginMetaObject> plugins;
};


class MgPluginsManager
{
public:
    MgPluginsManager(){}


    template<typename T>
    static bool registerPlugin(const QString & type,double version)
    {
        return MgPluginsManager::globalInstance()->registerPlugin(type,version,T::staticMetaObject);
    }

    bool registerPlugin(const QString & ,double version,const QMetaObject &);
    QObject * createObject(const QString & type,double version)const;


    static MgPluginsManager * globalInstance();


private:
    QHash<QString,MgPluginProvider> m_registeredTypes;
    static MgPluginsManager * m_globalInstance;

};

#endif // MGPLUGINSMANAGER_H
