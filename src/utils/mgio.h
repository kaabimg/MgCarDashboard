#ifndef MGIO_H
#define MGIO_H
#include <QString>
#include <QObject>


class MgMessagesManager : public QObject
{
    Q_OBJECT
public:

    MgMessagesManager(QObject * parent=0);
    static MgMessagesManager * instance();



public Q_SLOTS:

    void information(const QString &msg);
    void warning(const QString &);
    void error(const QString &);
    void log(const QString &);
    MgMessagesManager * globalMsgManager()const;

Q_SIGNALS:
    void informationMsg(QString msg);
    void warningMsg(QString msg);
    void errorMsg(QString msg);
    void logMsg(QString msg);


private:
    static MgMessagesManager * m_instance;
};


namespace MgIO {
    void information(const QString &msg);
    void warning(const QString &);
    void error(const QString &);
    void log(const QString &);
}



#endif // MGIO_H
