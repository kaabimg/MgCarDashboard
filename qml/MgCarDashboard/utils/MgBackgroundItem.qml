import QtQuick 2.0

Item {

    id : root

    anchors.fill: parent

    z : -1

    property alias backgroundColor: backgroundR.color
    property alias backgroundOpacity: backgroundR.opacity
    property alias borderWidth : borderR.width
    property alias borderColor: borderR.color


    function setInTransparentMode() {
        backgroundR.color = appSettings.colorSettings.intermediaryColor;
        backgroundR.opacity = 0.3;
    }

    function setInColorMode () {
        backgroundR.color = appSettings.colorSettings.darkColor;
        backgroundR.opacity = 0.8;
    }

    Rectangle {
        id : backgroundR
        anchors.fill: parent
        color  : appSettings.colorSettings.intermediaryColor
        opacity: 0.3
    }

    Rectangle {
        id : borderR
        anchors.fill: parent
        z : 1
        color : "transparent"
        border.width: 0
        visible: border.width > 0
        border.color: appSettings.colorSettings.intermediaryColor
    }

}
