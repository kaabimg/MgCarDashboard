import QtQuick 2.0


Item {

    id : statusBar
    property int dataStart



    MgBackgroundItem {
        borderWidth: 1


    }


    Text {
        x: dataStart
        y :0
        height: parent.height
        width: parent.width * 0.1
        color: appSettings.colorSettings.lightColor
        verticalAlignment : Text.AlignVCenter
        font.pointSize: appSettings.fontSettings.textPointSize

        Component.onCompleted: {
            font.family= appSettings.fontSettings.textFontFamily
        }

        text: car.externalTemperature+" °C"

    }


    MgDateTimeView {
        x : parent.width * 0.85
        y : 0
        height: parent.height
        width: parent.width * 0.1
    }




}
