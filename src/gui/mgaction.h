#ifndef MGACTION_H
#define MGACTION_H

#include <QObject>

class MgAction : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QByteArray name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QByteArray iconSource READ iconSource WRITE setIconSource NOTIFY iconSourceChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)


public:
    explicit MgAction(QObject *parent = 0);

    QByteArray name() const;

    QByteArray iconSource() const;

    bool enabled() const;

Q_SIGNALS:

    void nameChanged(QByteArray arg);
    void iconSourceChanged(QByteArray arg);
    void enabledChanged(bool arg);
    void triggered();

public Q_SLOTS:

    void setName(const QByteArray & arg);
    void setIconSource(const QByteArray & arg);
    void setEnabled(bool arg);


private:
    QByteArray m_name;
    QByteArray m_iconSource;
    bool m_enabled;
};



#endif // MGACTION_H
