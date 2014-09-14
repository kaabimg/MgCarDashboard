#ifndef MGCANMESSAGEABSTRACTDECODER_H
#define MGCANMESSAGEABSTRACTDECODER_H
#include <QObject>
#include <QList>
#include <QByteArray>

class MgAbstractStateMessagesProvider;
class MgCar;

class MgAbstractCanMessagesDecoder : public QObject
{
    Q_OBJECT
public:
    MgAbstractCanMessagesDecoder(QObject * parent=0):QObject(parent){}
    void  init( MgAbstractStateMessagesProvider * , MgCar * );
    virtual QList<QByteArray> supportedNodes()const {return QList<QByteArray>();}

protected Q_SLOTS:
    virtual void decodeMessage(const QByteArray & )=0;
    MgCar * car()const;

private:
    MgCar * m_car;
};

#endif // MGCANMESSAGEABSTRACTDECODER_H
