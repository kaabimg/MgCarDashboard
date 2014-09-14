import QtQuick 2.0

Item {
    id : item


    property var model
    property real labelWidthRatio : 0.5
    property int offset: width *0.01


    Item {
        id : labelText
        x : 0
        y:0
        width: parent.width * labelWidthRatio - parent.offset
        height: parent.height

        Text {
            anchors.centerIn:  parent

            text :model.label
            font.family: appSettings.fontSettings.textFontFamily
            font.pointSize: appSettings.fontSettings.textPointSize
            color: model.labelColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
    Item {
        x : labelText.width + 2 * parent.offset
        y:0
        width: parent.width - x
        height: parent.height
        Text {
            anchors.centerIn:  parent
            text :model.value
            font.family: appSettings.fontSettings.textFontFamily
            font.pointSize: appSettings.fontSettings.textPointSize
            color: model.valueColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
