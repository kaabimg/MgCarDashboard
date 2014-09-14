import QtQuick 2.0

QtObject {
    property string label
    property string value
    property color labelColor : appSettings.colorSettings.lightColor
    property color valueColor : appSettings.colorSettings.lightColor
}
