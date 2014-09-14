#ifndef MGCANBUSREADER_H
#define MGCANBUSREADER_H

#include <QSerialPort>
#include <QTimer>

#include "../../core/mgabstractstatemessagesprovider.h"

class MgCanBusReader : public MgAbstractStateMessagesProvider
{
    Q_OBJECT

public:

    enum CanBitRate
    {
        Bit10,
        Bit20,
        Bit50,
        Bit100,
        Bit125,
        Bit250,
        Bit500,
        Bit800,
        Bit1000,

    };


    Q_INVOKABLE explicit MgCanBusReader(QObject *parent = 0);
    virtual ~MgCanBusReader();

    bool isUsbConnected()const;
    bool isCanConnected()const;
    bool openUsb();
    void closeUsb();
    bool openCan();
    void closeCan();


    void setIdsFilter(const QList<QByteArray> & ids);
    bool setCanBitRate(CanBitRate);



Q_SIGNALS:
    void usbStateChanged(ConnectionState);
    void canStateChanged(ConnectionState);


    void okMessageReceived();
    void errorMessageReceived();

public Q_SLOTS:

    void connectToHardware();
    void disconnectFromHardware();

protected:
    void setUsbState(ConnectionState);
    void setCanState(ConnectionState);

protected Q_SLOTS:
    void readData();
    void tryToConnectToCan();

protected:
    void waitForAck();
    bool write(const QByteArray & );

private:
    ConnectionState m_usbState;
    ConnectionState m_canState;

    QSerialPort m_serialPort;
    bool m_lastMessageOk;
    QTimer m_connectionTimer;

};


#endif // MGCANBUSREADER_H
