#include "mgtouchhandler.h"
#include "qtquick2applicationviewer.h"

#include <QTouchEvent>
#include <QDebug>

#define SCREEN_WIDTH 1366

MgTouchHandler::MgTouchHandler(QObject *parent) :
    QObject(parent)
{
}

bool MgTouchHandler::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == parent())
    {
        if (event->type() == QEvent::TouchBegin ||
                event->type() == QEvent::TouchUpdate ||
                event->type() == QEvent::TouchEnd ||
                event->type() == QEvent::TouchCancel
                )

        {
            QTouchEvent *touchEvent = static_cast<QTouchEvent*>(event);

            QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();

            QPointF pos;

            for(int i=0;i<touchPoints.size();++i)
            {
                pos = touchPoints[i].pos();

                pos.setX(SCREEN_WIDTH - pos.x());
                touchPoints[i].setPos(pos);
            }
            touchEvent->setTouchPoints(touchPoints);
        }
    }
    return parent()->eventFilter(obj, event);
}
