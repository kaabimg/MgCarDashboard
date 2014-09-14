#ifndef MGUSBGPSPOSITIONSOURCE_H
#define MGUSBGPSPOSITIONSOURCE_H

#include <QNmeaPositionInfoSource>
class QSerialPort;
class MgUsbGpsPositionSource : public QNmeaPositionInfoSource
{
    Q_OBJECT
public:
    MgUsbGpsPositionSource(QObject * parent = 0);


private:
    QSerialPort * m_serialPort;
};

#endif // MGUSBGPSPOSITIONSOURCE_H
