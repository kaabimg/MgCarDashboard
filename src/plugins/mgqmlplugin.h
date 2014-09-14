#ifndef MGQMLPLUGIN_H
#define MGQMLPLUGIN_H

class MgQmlPlugin
{
public:
    MgQmlPlugin(){}


    virtual void init()= 0;
    virtual void clear() =0;
};

#endif // MGQMLPLUGIN_H
