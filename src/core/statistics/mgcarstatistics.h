#ifndef MGCARSTATISTICS_H
#define MGCARSTATISTICS_H

#include <QObject>
#include <QTimer>

class MgCar;

struct MgMeanCalculator {
    MgMeanCalculator():mean(0),count(0){}

    void update(float value){
        mean  = mean * (count/(count+1))+ value/(count+1);
        count ++;
    }
    void reset(){
        mean = 0;
        count = 0;
    }

    double mean;
    double count;
};


class MgCarStatistics : public QObject
{
    Q_OBJECT
public:
    explicit MgCarStatistics(QObject *parent = 0);
    void setCar(MgCar*);
    void startUpdate(int interval = 100);
    void stopUpdate();



public Q_SLOTS:
    virtual void reset(){}
protected Q_SLOTS:
    virtual void update(){}
protected:
    MgCar * car()const;

private:
    MgCar * m_car;
    QTimer m_updateTimer;


};

#endif // MGCARSTATISTICS_H
