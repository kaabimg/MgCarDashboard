#include "mgabstractcanmessagesdecoder.h"
#include "mgabstractstatemessagesprovider.h"
#include "mgcarstate.h"

void  MgAbstractCanMessagesDecoder::init( MgAbstractStateMessagesProvider * messagesProvider, MgCar * car)
{
    m_car = car;
    connect(messagesProvider,
            SIGNAL(messageReceived(QByteArray)),
            this,
            SLOT(decodeMessage(QByteArray))
            );
}

MgCar *MgAbstractCanMessagesDecoder::car() const
{
    return m_car;
}
