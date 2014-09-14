#include "mgfileshandler.h"
#include <QFile>

MgFilesHandler::MgFilesHandler(QObject *parent) :
    QObject(parent)
{
}


QString MgFilesHandler::readFileContent(const QString & path)const
{
    QFile file(path);
    if(file.open(QFile::ReadOnly))
    {
        QString content = file.readAll();
        file.close();
        return content;
    }
    return "";
}
