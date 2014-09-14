#ifndef MGFILESHANDLER_H
#define MGFILESHANDLER_H

#include <QObject>

class MgFilesHandler : public QObject
{
    Q_OBJECT
public:
    explicit MgFilesHandler(QObject *parent = 0);


public slots:
    QString readFileContent(const QString &)const;

};

#endif // MGFILESHANDLER_H
