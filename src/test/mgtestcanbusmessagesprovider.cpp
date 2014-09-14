#include "mgtestcanbusmessagesprovider.h"
#include <QFile>
#include <QDebug>




MgTestCanBusMessagesProvider::MgTestCanBusMessagesProvider(QObject * parent):
    MgAbstractStateMessagesProvider(parent),
    m_data("/home/ghaith/development/workspace/MgCarDashboard/MgCarDashboard/test_data/data")
{
    m_readTimer.setInterval(1);
    m_readTimer.setSingleShot(false);
    connect(&m_readTimer,SIGNAL( timeout()),this,SLOT(readLine()));
}


void MgTestCanBusMessagesProvider::connectToHardware()
{
    setConnectionState(Open);

    bool ok = m_data.open(QFile::ReadOnly | QFile::Text);

    qDebug()<<"file open"<<ok;
    m_readTimer.start();

}

void MgTestCanBusMessagesProvider::disconnectFromHardware()
{
    setConnectionState(Closed);

}

void MgTestCanBusMessagesProvider::readLine()
{
    QByteArray  line = m_data.readLine();
    if(line.endsWith('\n'))
        line.remove(line.size()-1,1);
    if(line .isEmpty() || line.isNull())
    {
        qDebug()<<"closing file";
        m_data.close();
        m_readTimer.stop();

    }

    Q_EMIT messageReceived(line);

}
