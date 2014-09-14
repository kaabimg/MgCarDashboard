#ifndef MGCAMERASELECTOR_H
#define MGCAMERASELECTOR_H

#include <QObject>
#include <QStringList>
class QCamera;
class QVideoDeviceSelectorControl;



class MgCameraSelector  : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* camera READ camera WRITE setCamera NOTIFY cameraChanged)
    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName NOTIFY deviceNameChanged)
    Q_PROPERTY(QStringList availableCameras READ availableCameras)


public:
    MgCameraSelector():m_camera(0),m_deviceSelector(0){}

    QStringList availableCameras()const;

    QObject* camera() const;
    QString deviceName() const;

public Q_SLOTS:
    void setDeviceName(QString arg);
    void setCamera(QObject* arg);

Q_SIGNALS:
    void cameraChanged(QObject* arg);
    void deviceNameChanged(QString arg);
    void cameraSourceChanged();

protected:
    void selectCamera();

private:
    QCamera* m_camera;
    QVideoDeviceSelectorControl *m_deviceSelector;
    QString m_deviceName;


};

#endif // MGCAMERASELECTOR_H
