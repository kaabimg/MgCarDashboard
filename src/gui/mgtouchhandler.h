#ifndef MGTOUCHHANDLER_H
#define MGTOUCHHANDLER_H

#include <QObject>

class MgTouchHandler : public QObject
{
    Q_OBJECT
public:
    explicit MgTouchHandler(QObject *parent = 0);

    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MGTOUCHHANDLER_H
