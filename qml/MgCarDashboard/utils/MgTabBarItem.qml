import QtQuick 2.0
import QtGraphicalEffects 1.0
Item {

    id : root

    property var tab
    property int selected : tab.visible

    signal showRequest(int index)

    //private:

    property int __tabsCount : parent.children.length

    x : 0
    y : tab.index*height
    width: parent.width
    height: parent.height/ __tabsCount


    Component.onCompleted: {
        showRequest.connect(parent.parent.showTab)
    }



    property int backgoundOffset: height * 0.05

    Rectangle {
        id : background
        x : backgoundOffset
        y : backgoundOffset
        width: parent.width - backgoundOffset*2
        height: parent.height - backgoundOffset*2
        radius: height *0.03
        z : -1
        color:  (root.tab.index %2 ?   appSettings.colorSettings.lightColor : appSettings.colorSettings.intermediaryColor)
        opacity: 0.2
    }

    Item {

        id : icon
        x : 0
        y : 0

        z :1
        width:  parent.height
        height: parent.height


        Image {
            id: iconImage
            source: tab.iconSource
            anchors.centerIn: parent
            width: parent.width * 0.7
            height: parent.height * 0.7


        }
    }


    Item  {

        anchors.fill  : parent


        Text {
            id: text


            anchors.fill: parent
            anchors.margins: 10

            horizontalAlignment:  Text.AlignRight
            verticalAlignment:  Text.AlignVCenter

            text: tab.title
            color:  root.selected ? appSettings.colorSettings.color1 : appSettings.colorSettings.lightColor
            font.pointSize:  appSettings.fontSettings.textPointSize
            font.family: appSettings.fontSettings.textFontFamily
            font.bold: root.selected


        }


        //        Item {
        //            id : outliner

        //            anchors.fill : parent
        //            visible: root.selected

        //            property int lineWidth : 2


        //            Rectangle {
        //                x: 0
        //                y : 0
        //                width: parent.width
        //                height: outliner.lineWidth
        //                color : appSettings.secondaryColor
        //            }

        //            Rectangle {
        //                x: 0
        //                y : outliner.height-outliner.lineWidth
        //                width: parent.width
        //                height: outliner.lineWidth
        //                color : appSettings.secondaryColor
        //            }

        //            Rectangle {
        //                x: outliner.width - outliner.lineWidth
        //                y : 0
        //                width: outliner.lineWidth
        //                height: outliner.height
        //                color : appSettings.secondaryColor
        //            }
        //        }

    }



    MouseArea {
        anchors.fill: parent

        onClicked: {
            if(!root.selected) root.showRequest(root.tab.index)
        }
    }
}
