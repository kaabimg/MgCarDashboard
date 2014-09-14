import QtQuick 2.2





Item {

    id : root

    property var labels : ["Drive","Maneuver","Navigation","Settings"]
    property int itemHeight : height / labels.length

    property int selectedItemIndex : 0

    property bool isInNavigationMode : selectedItemIndex === 2

    function setSelectedItem(index){
        selectedItemIndex = index;
    }


    onIsInNavigationModeChanged: {
        if(isInNavigationMode)
            background.setInColorMode();
        else
            background.setInTransparentMode();
    }

    MgBackgroundItem{
        id : background
        borderWidth: 1
    }


    MgSmoothNumber {
        id : backgroundY
        value : selectedItemIndex * itemHeight

    }

    MgBackgroundItem {
        anchors.fill: null
        x : 0
        y : backgroundY.value
        width: parent.width
        height: root.itemHeight
        backgroundColor: appSettings.colorSettings.intermediaryColor
    }

    Repeater {
        model: root.labels.length


        Item {
            id : item
            x: 0
            y : index * root.itemHeight
            width: parent.width
            height: root.itemHeight

            property bool selected: index == root.selectedItemIndex

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    root.setSelectedItem(index);
                }
            }

            Text {
                anchors.fill: parent
                text : root.labels[index]
                color: item.selected ? appSettings.colorSettings.color1 :  appSettings.colorSettings.lightColor
                font.family: appSettings.fontSettings.textFontFamily
                font.pointSize: appSettings.fontSettings.textPointSize
                font.bold: item.selected
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }

        }

    }



}

