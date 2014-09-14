import QtQuick 2.2
import Mg 1.0


Item {
    id : root

    property real  level : 0
    property alias model : info.model
    property alias color : line.color1
    property alias labelWidthRatio: info.labelWidthRatio

    MgInformationItem {
        id : info
        width: parent.width
        height: parent.height/2
        anchors.top: parent.top


    }

    MgLineView {
        id : line
        width: parent.width
        height: parent.height/2
        anchors.bottom: parent.bottom
        size : height
        startPoint: Qt.point(0,height/2)
        endPoint: Qt.point(root.level * width,height/2)
        shadingMode: MgLineView.Flat

        opacity: 0.8

        Rectangle {
            anchors.fill: parent
            color: root.color
            opacity: 0.2
            z : -1
        }
    }
    Rectangle {
        id : backdround
        anchors.fill: parent
        color:  appSettings.colorSettings.intermediaryColor
        radius: Math.min(width,height) * 0.05
        opacity: 0.2
        z : -1
    }



}
