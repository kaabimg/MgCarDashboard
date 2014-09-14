#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "src/mgcardashboardmainplugin.h"
#include <QGeoServiceProvider>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDebug>

#include "src/core/mgcarstate.h"

#include "src/test/test_can_decoder.h"
#include "src/gui/mgtouchhandler.h"
#include "src/settings/mgapplicationsettings.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    MgApplicationSettings appSettings;
    appSettings.load();


    MgCarDashboardMainPlugin mainPlugin;
    mainPlugin.init();

    MgCar car;
    car.setDecoderPlugin("canBusToPrius2");
    car.setDecoderPluginVersion(1.0);
//    car.setPhysicalConnectionPlugin("canusb");
    car.setPhysicalConnectionPlugin("test-provider");
    car.setPhysicalConnectionPluginVersion(1.0);


    QtQuick2ApplicationViewer viewer;



    viewer.engine()->rootContext()->setContextProperty("appSettings",&appSettings);
    viewer.engine()->rootContext()->setContextProperty("car",&car);
    viewer.setMainQmlFile(QStringLiteral("qml/MgCarDashboard/main.qml"));


    MgTouchHandler * touchHandler = new MgTouchHandler(&viewer);
    viewer.installEventFilter(touchHandler);

    if(app.arguments().contains("-desktop"))
    {
        viewer.resize(1366,768);

    }
    viewer.show();

    car.connectToHardware();

    int ret  = app.exec();

    mainPlugin.clear();
    return ret;
}
