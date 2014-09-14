import QtQuick 2.0

Item {
    id : root

    property int xCenter
    property int yCenter
    property int value
    property bool active : true

//private:
    x : xCenter - width/2
    y : yCenter - height/2


    Text {
        id: text
        text: root.value
        anchors.centerIn: parent
        font.pointSize: appSettings.fontSettings.speedGraduationsPointSize
        font.family: appSettings.fontSettings.speedGraduationsFontFamily
        color: root.active ? Qt.lighter(appSettings.colorSettings.color1) : appSettings.colorSettings.intermediaryColor

    }
}
