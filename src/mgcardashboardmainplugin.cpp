#include "mgcardashboardmainplugin.h"

#include <QtQml>
#include "plugins/prius2/mgprius2canmessagesdecoder.h"
#include "plugins/can/mgcanbusreader.h"
#include "utils/mgio.h"
#include "utils/mgcameraselector.h"
#include "core/mgpluginsmanager.h"
#include "core/mgcarstate.h"
#include "core/mgpointsprovider.h"
#include "core/statistics/mgbatterystatistics.h"
#include "core/statistics/mgdrivestatistics.h"
#include "gui/mgaction.h"
#include "gui/mgactionsview.h"
#include "gui/mggraphview.h"
#include "gui/mgarcview.h"
#include "gui/mggaugecontroller.h"
#include "gui/mglineview.h"

#include "plugins/positioning/mgusbgpspositionsource.h"

#include "test/mgtestcanbusmessagesprovider.h"

#include "settings/mgapplicationsettings.h"


void MgCarDashboardMainPlugin::init()
{
    MgPluginsManager::registerPlugin<MgPrius2CanMessagesDecoder>("canBusToPrius2",1.0);
    MgPluginsManager::registerPlugin<MgCanBusReader>("canusb",1.0);
    MgPluginsManager::registerPlugin<MgTestCanBusMessagesProvider>("test-provider",1.0);


    qmlRegisterType<MgColorSettings>("Mg",1,0,"MgAColorSettings");
    qmlRegisterType<MgFontSettings>("Mg",1,0,"MgFontSettings");

    qmlRegisterType<MgMessagesManager>("Mg", 1, 0, "MgMessagesManager");
    qmlRegisterType<MgCar>("Mg", 1, 0, "MgCar");
//    qmlRegisterType<MgBatteryStatistics>("Mg", 1, 0, "MgBatteryStatistics");
    qmlRegisterType<MgDriveStatistics>("Mg", 1, 0, "MgDriveStatistics");
    qmlRegisterType<MgCameraSelector>("Mg", 1, 0, "MgCameraSelector");
    qmlRegisterType<MgUsbGpsPositionSource>("Mg", 1, 0, "MgUsbGpsPositionSource");
    qmlRegisterType<MgGraphView>("Mg", 1, 0, "MgGraphView");
    qmlRegisterType<MgArcView>("Mg", 1, 0, "MgArcView");
    qmlRegisterType<MgLineView>("Mg", 1, 0, "MgLineView");

    qmlRegisterType<MgGaugeController>("Mg", 1, 0, "MgGaugeController");
    qmlRegisterType<MgPointsProvider>("Mg", 1, 0, "MgPointsProvider");
    qmlRegisterType<ProviderTest>("Mg", 1, 0, "ProviderTest");
    qmlRegisterType<MgAction>("Mg", 1, 0, "MgAction");

//    qmlRegisterType<MgActionsView>("Mg", 1, 0, "MgActionsView");


}
void MgCarDashboardMainPlugin::clear()
{

}
