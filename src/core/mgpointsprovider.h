#ifndef MGPOINTSPROVIDER_H
#define MGPOINTSPROVIDER_H
#include <QObject>
#include <QQmlParserStatus>
#include <QMetaProperty>
#include <QTimer>
#include <QElapsedTimer>



class MgPointsProvider : public QObject,public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QObject* source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QByteArray targetProperty READ targetProperty WRITE setTargetProperty NOTIFY targetPropertyChanged)
    Q_PROPERTY(int period READ period WRITE setPeriod NOTIFY periodChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(float mean READ mean NOTIFY meanChanged)



public:
    MgPointsProvider(QObject * parent = 0);

    QObject* source() const;
    QByteArray targetProperty() const;
    int period() const;
    bool active() const;

    void classBegin(){}

    void componentComplete() ;

    float mean() const;




public Q_SLOTS:

    void setSource(QObject* arg);
    void setTargetProperty(const QByteArray & arg);
    void setPeriod(int arg);
    void setActive(bool arg);
    void resetStatistics();
    void start();
    void stop();

Q_SIGNALS:
    void sourceChanged(QObject* arg);
    void targetPropertyChanged(QByteArray arg);
    void periodChanged(int arg);
    void activeChanged(bool arg);

    void newPoint(float time,float value);
    void meanChanged(float arg);

protected:
    void addPoint(float time,float value);

private Q_SLOTS:
    void updateValue();

private:
    void tryToSetMetaProperty();
    void tryToStart();
    void init();
    void setMean(float);



private:
    QObject* m_source;
    QByteArray m_targetProperty;
    QTimer m_updateTimer;
    bool m_active;
    QMetaProperty  m_property;
    bool m_propertyValid,m_initialized;
    QElapsedTimer m_elapsedTimer;
    float m_mean;
    int m_totalPoints;
    float m_lastPointY;
    float m_lastPointX;
    float m_lastTime;
    float m_lastValue;
};

#include <math.h>
#include <QDebug>

class ProviderTest : public MgPointsProvider
{
    Q_OBJECT
public:
    ProviderTest()
    {
        QTimer * timer = new QTimer(this);
        timer->setInterval(500);
        timer->setSingleShot(false);
        connect(timer,SIGNAL(timeout()),SLOT(onTimeout()));
        m_timer.start();
        timer->start();
    }

    Q_SLOT void onTimeout()
    {
        addPoint(m_timer.elapsed(),sin(m_timer.elapsed()*0.0001));
    }

    QElapsedTimer m_timer;
};


#endif // MGPOINTSPROVIDER_H
