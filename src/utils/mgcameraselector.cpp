#include "mgcameraselector.h"

#include <QCamera>

#include <QVideoDeviceSelectorControl>
#include <QMediaService>




QStringList MgCameraSelector::availableCameras()const
{
    QStringList cameras;
//    foreach (const QCameraInfo & info,QCameraInfo::availableCameras())
  //  {
    //    cameras<<info.deviceName();
    //}

    return cameras;


}

QObject *MgCameraSelector::camera() const
{
    return m_camera;
}

void MgCameraSelector::setCamera(QObject *arg)
{
    if (m_camera != arg) {
        m_camera = qvariant_cast<QCamera *>(arg->property("mediaObject"));
        Q_EMIT cameraChanged(arg);
    }

    if(!m_camera)
        return;

    QMediaService *service = m_camera->service();
    m_deviceSelector = qobject_cast<QVideoDeviceSelectorControl*>(service->requestControl(QVideoDeviceSelectorControl_iid));

    selectCamera();
}

QString MgCameraSelector::deviceName() const
{
    return m_deviceName;
}

void MgCameraSelector::setDeviceName(QString arg)
{
    if (m_deviceName != arg) {
        m_deviceName = arg;
        Q_EMIT deviceNameChanged(arg);
    }

    selectCamera();

}



void MgCameraSelector::selectCamera()
{
    if(!m_camera || !m_deviceSelector || m_deviceName.isEmpty())
        return;

    m_camera->unload();

    int id = 0;
    bool found= false;

    foreach (const QString & device, availableCameras()) {
        if(m_deviceName == device)
        {
            found = true;
            break;
        }
        else
            id++;
    }
    if(found)
    {
        m_deviceSelector->setSelectedDevice(id);
        Q_EMIT cameraSourceChanged();
    }





}

