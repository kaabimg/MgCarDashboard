import QtQuick 2.0

Item {
    id : root

    property string title : ""
    property string iconSource : ""
    property int index : -1
    property bool isSelected : false


    anchors.fill: parent

    visible: (index === parent.visibleIndex)


    Component.onCompleted: children[0].anchors.fill = root




}
