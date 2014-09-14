import QtQuick 2.0

Item {

    id : root

    property string title
    property list<MgInformationItemModel> items
    property int itemsCount : items.length
    property real labelWidthRatio : 0.5

    property int itemHeight : height/(itemsCount +1 )

    Item {
        x : 0
        y:0
        width: parent.width
        height: itemHeight
        Text {
            anchors.centerIn:  parent
            text :root.title
            font.family: appSettings.fontSettings.textFontFamily
            font.pointSize: appSettings.fontSettings.textPointSize
            color: appSettings.colorSettings.lightColor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }



    Repeater {
        model : root.itemsCount
        MgInformationItem {
            x: 0
            y : (index+1) * root.itemHeight
            width: root.width
            height: root.itemHeight
            labelWidthRatio: root.labelWidthRatio
            model: root.items[index]


            MgBackgroundItem {
                 backgroundColor: index %2 ? appSettings.colorSettings.darkColor : appSettings.colorSettings.intermediaryColor
            }
        }

    }



}
