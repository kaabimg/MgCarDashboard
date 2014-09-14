import QtQuick 2.0
import "../utils"
Item {
    id : root
    width: parent.width * 0.1
    height: parent.height * 0.05
    x : (parent.width - width) * 0.5
    y : parent.height * 0.6

    property string value : "000000"

    property int digitsCount : 6
    property int itemWidth : width /digitsCount

    Rectangle {
        anchors.fill: parent
        color: appSettings.colorSettings.intermediaryColor
        opacity: 0.3
        z : -1
    }


    Repeater {
        model: root.digitsCount

        Item  {
            id: digit
            x : index * root.itemWidth
            y : 0
            width: root.itemWidth
            height: root.height

            property string value :  root.value.length > index ? root.value[index] : "0"

            Text {


                anchors.fill: parent
                text : digit.value
                color: appSettings.colorSettings.lightColor
                font.family: appSettings.fontSettings.speedGaugeFontFamily
                font.pointSize: appSettings.fontSettings.speedGraduationsPointSize

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

        }



    }



}

