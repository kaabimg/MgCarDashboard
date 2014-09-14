#ifndef MGABSTRACTSTATEMESSAGESPROVIDER_H
#define MGABSTRACTSTATEMESSAGESPROVIDER_H

#include <QObject>
#include <QByteArray>


class MgAbstractStateMessagesProvider : public QObject
{
    Q_OBJECT

    Q_ENUMS(ConnectionState)
    Q_PROPERTY(ConnectionState connectionState READ connectionState NOTIFY connectionStateChanged)

public:
    enum ConnectionState{Open,Closed};
    explicit MgAbstractStateMessagesProvider(QObject *parent = 0):QObject(parent),m_connectionSate(Closed){}

public Q_SLOTS:

    virtual void connectToHardware()=0;
    virtual void disconnectFromHardware()=0;

   ConnectionState connectionState()const{return m_connectionSate;}

Q_SIGNALS:
      void messageReceived(QByteArray);
      void connectionStateChanged(ConnectionState);

protected:
      void setConnectionState(ConnectionState s)
      {
          if(m_connectionSate != s)
          {
              m_connectionSate = s;
              Q_EMIT connectionStateChanged(s);
          }
      }

private:
      ConnectionState m_connectionSate;
};

#endif // MGABSTRACTSTATEMESSAGESPROVIDER_H
