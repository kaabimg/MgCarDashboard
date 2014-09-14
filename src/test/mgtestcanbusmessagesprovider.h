#ifndef MGTESTCANBUSMESSAGESPROVIDER_H
#define MGTESTCANBUSMESSAGESPROVIDER_H

#include "../core/mgabstractstatemessagesprovider.h"

#include <QFile>
#include <QTimer>


class MgTestCanBusMessagesProvider: public MgAbstractStateMessagesProvider
{
    Q_OBJECT
public:
    Q_INVOKABLE MgTestCanBusMessagesProvider(QObject * parent=0);

    void connectToHardware();
    void disconnectFromHardware();

protected Q_SLOTS:
    void readLine();

private:
    QTimer m_readTimer;
    QFile m_data;

};


#endif // MGTESTCANBUSMESSAGESPROVIDER_H
