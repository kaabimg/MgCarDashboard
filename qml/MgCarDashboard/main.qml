import QtQuick 2.0
import "utils"

Rectangle {

    property int offset: 10

    Rectangle {

        x: 0
        y : 0
        width: offset
        height: parent.height

        color : "yellow"

    }
    color : "black"

    MgCarDashboard {
        x: offset
        y : 0
        width: parent.width -offset
        height: parent.height
    }
}


