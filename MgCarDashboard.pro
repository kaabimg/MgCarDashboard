# Add more folders to ship with the application, here
folder_01.source = qml/MgCarDashboard
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    src/core/mgabstractcanmessagesdecoder.cpp \
    src/core/mgcarstate.cpp \
    src/core/mgpluginsmanager.cpp \
    src/plugins/prius2/mgprius2canmessagesdecoder.cpp \
    src/utils/mgfileshandler.cpp \
    src/utils/mgio.cpp \
    src/plugins/can/mgcanbusreader.cpp \
    src/mgcardashboardmainplugin.cpp \
    src/utils/mgcameraselector.cpp \
    src/gui/mggraphview.cpp \
    src/gui/mgaction.cpp \
    src/gui/mgactionsview.cpp \
    src/core/mgpointsprovider.cpp \
    src/plugins/positioning/mgusbgpspositionsource.cpp \
    src/test/test_can_decoder.cpp \
    src/gui/mgtouchhandler.cpp \
    src/settings/mgapplicationsettings.cpp \
    src/test/mgtestcanbusmessagesprovider.cpp \
    src/gui/mggaugecontroller.cpp \
    src/gui/mgarcview.cpp \
    src/settings/mgcolorsettings.cpp \
    src/settings/mgfontsettings.cpp \
    src/gui/mglineview.cpp \
    src/core/statistics/mgbatterystatistics.cpp \
    src/core/statistics/mgcarstatistics.cpp \
    src/core/statistics/mgdrivestatistics.cpp


# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()


QT += serialport multimedia 3d positioning location




HEADERS += \
    src/core/mgabstractcanmessagesdecoder.h \
    src/core/mgabstractstatemessagesprovider.h \
    src/core/mgcarstate.h \
    src/core/mgpluginsmanager.h \
    src/plugins/prius2/mgprius2canmessagesdecoder.h \
    src/utils/mgfileshandler.h \
    src/utils/mgglobal.h \
    src/utils/mgio.h \
    src/plugins/can/mgcanbusreader.h \
    src/plugins/mgqmlplugin.h \
    src/mgcardashboardmainplugin.h \
    src/utils/mgcameraselector.h \
    src/gui/mggraphview.h \
    src/gui/mgaction.h \
    src/gui/mgactionsview.h \
    src/core/mgpointsprovider.h \
    src/plugins/positioning/mgusbgpspositionsource.h \
    src/test/test_can_decoder.h \
    src/gui/mgtouchhandler.h \
    src/settings/mgapplicationsettings.h \
    src/test/mgtestcanbusmessagesprovider.h \
    src/gui/mggaugecontroller.h \
    src/gui/mgarcview.h \
    src/settings/mgcolorsettings.h \
    src/settings/mgfontsettings.h \
    src/gui/mglineview.h \
    src/core/statistics/mgbatterystatistics.h \
    src/core/statistics/mgcarstatistics.h \
    src/core/statistics/mgdrivestatistics.h \
    src/gui/mgtexturesprovider.h


OTHER_FILES += \
    qml/MgCarDashboard/carinformation/MgCarInformationView.qml \
    qml/MgCarDashboard/maneuver/MgManeuverView.qml \
    qml/MgCarDashboard/navigation/MgNavigationView.qml \
    qml/MgCarDashboard/power/MgPowerView.qml \
    qml/MgCarDashboard/utils/MgDateTimeView.qml \
    qml/MgCarDashboard/utils/mgactionsviewutils.js \
    qml/MgCarDashboard/driveinformation/MgDriveInformationView.qml \
    shaders/arc.vsh \
    shaders/arc.fsh \
    shaders/arc_flat.fsh \
    shaders/arc_inner_radius_to_outer_radius_linear_gradient.fsh \
    shaders/arc_inner_radius_to_outer_radius_exponential_gradient.fsh \
    shaders/arc_glow.fsh \
    shaders/arc_glow_thin.fsh \
    qml/MgCarDashboard/utils/MgSmoothNumber.qml \
    shaders/line.vsh \
    shaders/line_flat.fsh \
    shaders/line_glow.fsh \
    qml/MgCarDashboard/utils/MgLevelView.qml


RESOURCES += \
    images.qrc \
    shaders.qrc
