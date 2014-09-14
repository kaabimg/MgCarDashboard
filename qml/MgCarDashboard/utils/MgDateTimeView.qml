import QtQuick 2.0

Item {

    Timer {
        id : updateTimer
        interval: 1000
        onTriggered: text.update()
        repeat: true
    }

    Text {
        id : text
        anchors.fill: parent
        color: appSettings.colorSettings.lightColor
        verticalAlignment : Text.AlignVCenter
        text : Qt.formatDateTime(new Date(), "MMMM d hh:mm")

        font.pointSize: appSettings.fontSettings.textPointSize
        font.family: appSettings.fontSettings.textFontFamily


        function update()
        {
            text.text = Qt.formatDateTime(new Date(), "MMMM d hh:mm");
        }



    }
    Component.onCompleted: updateTimer.start()
}
