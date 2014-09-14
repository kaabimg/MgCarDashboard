#ifndef MGPRIUS2CANMESSAGESDECODER_H
#define MGPRIUS2CANMESSAGESDECODER_H

#include "../../core/mgabstractcanmessagesdecoder.h"
#include <QTimer>
class MgCarStatePrius2;



class MgPrius2CanMessagesDecoder : public MgAbstractCanMessagesDecoder
{
    Q_OBJECT
public:
    Q_INVOKABLE MgPrius2CanMessagesDecoder(QObject * parent=0);
    ~MgPrius2CanMessagesDecoder();
    QList<QByteArray> supportedNodes()const;


protected Q_SLOTS:
    void updateCarState();
protected:
    virtual void decodeMessage(const QByteArray & );
    friend class test_can_decoder;

private:
    MgCarStatePrius2 * m_carState;
    QTimer m_updateTimer;

};

#endif // MGPRIUS2CANMESSAGESDECODER_H
