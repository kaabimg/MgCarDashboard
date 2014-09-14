#ifndef MGDISKVIEW_H
#define MGDISKVIEW_H

#include <QQuickItem>

class MgDiskView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(float startRadius READ startRadius WRITE setStartRadius NOTIFY startRadiusChanged)
    Q_PROPERTY(float endRadius READ endRadius WRITE setEndRadius NOTIFY endRadiusChanged)
    Q_PR
public:
    explicit MgDiskView(QQuickItem *parent = 0);

signals:

public slots:

};

#endif // MGDISKVIEW_H
