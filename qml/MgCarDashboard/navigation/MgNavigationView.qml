import QtQuick 2.2
import QtPositioning 5.3
import QtLocation 5.3

import "../utils"

Item {

    id : root

    property int mapOffset


    Map {
        id : map
        anchors.fill: parent


        zoomLevel: 10
        maximumZoomLevel: 18.99
        center {
            latitude: 45.204969
            longitude: 5.747393
        }
        plugin: Plugin {
            name: "mg-osm-offline"
            parameters: [
                PluginParameter {
                    name: "tilesDirectory"
                    value: "/home/ghaith/development/osm_data/tiles"
                }
            ]
        }
        gesture.enabled : true

    }


    Item {
        id: controls

        x: parent.width - width
        y : (parent.height - height) * 0.5

        width: itemSize
        height: itemSize * itemsCount

        property int itemsCount : 2
        property int itemSize : parent.width * 0.045


        property color selectedColor : appSettings.colorSettings.intermediaryColor
        property color unselectedColor : appSettings.colorSettings.darkColor

        property color itemColor : appSettings.colorSettings.lightColor


        property real scaleFactor : 1.02

        property real backgroundOpacity : 0.8

        Item {
            id : zoomIn
            x : 0
            y : 0
            width: controls.itemSize
            height: controls.itemSize

            MgBackgroundItem{
                id : zoomInBackground
                backgroundColor: controls.unselectedColor
                backgroundOpacity: controls.backgroundOpacity
            }


            Rectangle {
                width: parent.width * 0.1
                height: parent.height *0.6
                radius: width *0.5
                anchors.centerIn: parent
                color : controls.itemColor
            }

            Rectangle {
                width: parent.width * 0.6
                height: parent.height *0.1
                radius: height *0.5
                anchors.centerIn: parent
                color : controls.itemColor
            }

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    zoomInBackground.backgroundColor = controls.selectedColor;
                    map.zoomLevel *= controls.scaleFactor;
                }
                onReleased: zoomInBackground.backgroundColor = controls.unselectedColor
            }

        }
        Item {
            id : zoomOut
            x : 0
            y : controls.itemSize
            width: controls.itemSize
            height: controls.itemSize
            MgBackgroundItem{
                id : zoomOutBackground
                backgroundColor: controls.unselectedColor
                backgroundOpacity: controls.backgroundOpacity

            }

            Rectangle {
                width: parent.width * 0.6
                height: parent.height *0.1
                radius: height *0.5
                anchors.centerIn: parent
                color : controls.itemColor
            }

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    zoomOutBackground.backgroundColor = controls.selectedColor;
                    map.zoomLevel /= controls.scaleFactor;
                }
                onReleased: zoomOutBackground.backgroundColor = controls.unselectedColor
            }

        }
        Item {
            id : zoomValue
            x : 0
            y : controls.itemSize * 2
            width: controls.itemSize
            height: controls.itemSize
            MgBackgroundItem{
                id : zoomValueBackground
                backgroundColor: controls.unselectedColor
                backgroundOpacity: controls.backgroundOpacity

            }
            Text {
                anchors.fill: parent
                text : map.zoomLevel.toFixed(1)
                color: controls.itemColor
                font.family: appSettings.fontSettings.textFontFamily
                font.pointSize: appSettings.fontSettings.textPointSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }


        }

    }

}
