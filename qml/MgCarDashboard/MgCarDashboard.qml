import QtQuick 2.0
import Mg 1.0
import QtGraphicalEffects 1.0
import "utils"
import "driveinformation"
import "carinformation"
import "maneuver"
import "power"
import "navigation"


Item {
    id : root

    property real statusBarHeight : height * 0.075

    MgUsbGpsPositionSource {


        onPositionUpdated: {
            console.log("----- New position");
            //            console.log(update)
        }
    }


    property int dataStart : width * 0.15

    MgStatusBar {
        id : statusBar

        property int offset : 10
        x : offset
        y :  offset
        width: root.width - 2* offset
        height: root.statusBarHeight - 2* offset
        dataStart : root.dataStart

    }


    Item {

        id : mainView
        x : 0
        y : root.statusBarHeight
        z : .5
        width: root.width
        height: root.height - y



        MgNavigationList {
            id : navigationList
            x : root.height * 0.0125
            y : x /2
            width: 200
            height: 200
            z : 1
        }
        property alias visibleIndex :navigationList.selectedItemIndex

        MgTab {
            id : driveTab
            title : navigationList.labels[index]
            index: 0
            MgDriveInformationView {
                anchors.fill: parent
            }
        }

        MgTab {
            id : maneuverTab
            title : navigationList.labels[index]
            index: 1
            MgManeuverView {anchors.fill: parent}
        }

        MgTab {

            id : navigationTab
            title : navigationList.labels[index]
            index: 2
            MgNavigationView {
                anchors.fill: parent
            }
        }

        MgTab {
            id : settingsTab
            title : navigationList.labels[index]
            index: 3
            Item {anchors.fill: parent}
        }

    }
}

