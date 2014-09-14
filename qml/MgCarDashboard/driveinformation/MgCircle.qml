import QtQuick 2.0

Rectangle {
    id : root
    property int diameter
    property color borderColor
    property int borderWidth
    //
    width: diameter
    height: diameter
    radius: diameter/2

    border.color : borderColor
    border.width: borderWidth

}
