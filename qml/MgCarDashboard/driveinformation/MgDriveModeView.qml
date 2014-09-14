import QtQuick 2.0
import "../utils"
Item {

    id : root
    property int margin:height * 0.3
    property string currentMode : "P"


    Rectangle {
        id : background
        anchors.fill: parent
        radius: root.margin
        color :  "transparent"
        border.width: 2
        border.color: appSettings.colorSettings.intermediaryColor
        opacity: 0.8

    }


    property int itemWidth: (width-margin*2)/5
    property var texts : ["P","N","D","B","R"]

    MgSmoothNumber {
        id : currentIndex
        value : texts.indexOf(root.currentMode)
    }


    Rectangle {
        x : root.margin + currentIndex.value * root.itemWidth
        y : 0
        width: root.itemWidth
        height: root.height
        color : appSettings.colorSettings.lightColor
        opacity: 0.2
    }

    Repeater{
        id : repeater
        model :5
        z : 1
        Item {
            id : driveItem
            x : root.margin + index * root.itemWidth
            y : 0
            width: root.itemWidth
            height: root.height
            property bool active : texts.indexOf(root.currentMode) === index
            Text {
                anchors.fill : parent
                text:root.texts[index]
                color: driveItem.active ? appSettings.colorSettings.color1 : appSettings.colorSettings.intermediaryColor
                font.family: appSettings.fontSettings.textFontFamily
                font.pointSize: appSettings.fontSettings.speedGraduationsPointSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }
        }

    }
}
