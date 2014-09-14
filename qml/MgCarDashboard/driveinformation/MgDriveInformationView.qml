import QtQuick 2.2
import "../utils"
import Mg 1.0

Item {

    id : root


    property int __margin : width * 0.01


    states: [
        State {
            name: "globalView"
            PropertyChanges {
                target: fuelConsumptionGraph
                x : parent.width -width - parent.__margin
                y : parent.height * 0.79
                width: parent.width * 0.29
                height: parent.height * 0.2
            }
        },
        State {
            name: "fuelConsumptionView"
            PropertyChanges {
                target: fuelConsumptionGraph
                x :  parent.__margin
                y :  parent.__margin
                width: parent.width * - 2 * parent.__margin
                height: parent.height -2 *  parent.__margin
            }
        }

    ]


    property real gaugeDiameter : height * 0.88

    MgCarGauge {
        id : gauge
        anchors.fill: parent
        diameter: root.gaugeDiameter
        z : -1
    }


    Item {
        id : instantaneousFuelConsumption
        width: parent.width * 0.1
        height: parent.height * 0.05
        x : (parent.width - width) * 0.5
        y : parent.height * 0.55

        MgBackgroundItem {

        }

        Text {//value

            anchors.fill: parent
            anchors.margins: parent.width * 0.03
            text : car.instantaneousFuelConsumption.toFixed(2)
            color: appSettings.colorSettings.lightColor
            font.family: appSettings.fontSettings.speedGaugeFontFamily
            font.pointSize: appSettings.fontSettings.speedGraduationsPointSize

            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
        }
    }
    Text {//unit

        anchors.left: instantaneousFuelConsumption.right
        y : instantaneousFuelConsumption.y
        width: instantaneousFuelConsumption.width
        height: instantaneousFuelConsumption.height
        text : " l/100 Km"
        color: appSettings.colorSettings.lightColor
        font.family: appSettings.fontSettings.speedGaugeFontFamily
        font.pointSize: appSettings.fontSettings.speedGraduationsPointSize * 0.5

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }


    MgDistanceView {
        id : totalDistanceItem
        width: parent.width * 0.1
        height: parent.height * 0.05
        x : (parent.width - width) * 0.5
        y : parent.height * 0.61
        digitsCount: 6
        value: car.totalKilometers.toString()
    }
    Text {//unit

        anchors.left: totalDistanceItem.right
        y : totalDistanceItem.y
        width: totalDistanceItem.width
        height: totalDistanceItem.height
        text : " Km"
        color: appSettings.colorSettings.lightColor
        font.family: appSettings.fontSettings.speedGaugeFontFamily
        font.pointSize: appSettings.fontSettings.speedGraduationsPointSize * 0.5

        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }



    Item {
        id : informationPanel
        x : root.width - width-  root.__margin
        y : root.__margin
        width: root.width * 0.2
        height: root.height - 2 * root.__margin

        MgSmoothNumber {
            id : batteryLevel
            value : car.batteryLevel
        }


        MgLevelView {
            id : batteryLevelView

            x : 0
            y : 0

            width: parent.width
            height: parent.height * 0.1

            labelWidthRatio : 0.7

            level  : batteryLevel.value / 100.

            model: MgInformationItemModel {
                label:  "Battery level"
                value:  car.batteryLevel+" %"
                labelColor: appSettings.colorSettings.lightColor
                valueColor: appSettings.colorSettings.lightColor
            }
            color: appSettings.colorSettings.color3
        }




        MgSmoothNumber {
            id : fuelLevel
            value : car.fuelLevel
        }

        MgLevelView {
            id : fuelLevelView


            x : 0
            y : height

            width: parent.width
            height: parent.height * 0.1

            labelWidthRatio : 0.7

            level  : fuelLevel.value / 46.

            model: MgInformationItemModel {
                label: "Fuel level"
                value: car.fuelLevel+" L"
                labelColor: appSettings.colorSettings.lightColor
                valueColor: appSettings.colorSettings.lightColor
            }
            color: appSettings.colorSettings.color2
        }


        MgGraphView {
            id : fuelConsumptionGraph

            x : 0
            y : parent.height *  0.3

            width: parent.width
            height: parent.height * 0.2


            minY  : 0
            maxY  : 20
            timeWindow : 60 * 1000
            graphPointsSize :  60 * 5

            graphColor : appSettings.colorSettings.color2
            fillColor: Qt.rgba(
                           appSettings.colorSettings.color2.r,
                           appSettings.colorSettings.color2.g,
                           appSettings.colorSettings.color2.b,
                           0.4);

            graphLineWidth :   1
            pointsProvider: MgPointsProvider {
                id : pointsProvider
                source: car
                targetProperty: "instantaneousFuelConsumption"
                period: 200
            }

            Component.onCompleted: {
                pointsProvider.start();
            }

            Rectangle {
                anchors.fill: parent
                color: appSettings.colorSettings.intermediaryColor
                opacity:0.2
                z : -1
            }

            Item {
                id: grid
                anchors.fill: parent

                property real positionOffset : 1

                Repeater {
                    model : 3
                    Rectangle {
                        x:0
                        width: parent.width
                        y : parent.height * (index + 1) * 0.25 - parent.positionOffset
                        height: parent.positionOffset
                        color: appSettings.colorSettings.lightColor
                        opacity: 0.5

                    }
                }
            }

            Item {
                id : graphGraduations
                x: -width * 1.2
                y : 0
                width: parent.width * 0.15
                height: parent.height

                property int itemsCount : 4
                property int offset : height * 0.085


                Repeater {
                    id : textRepeater
                    model : graphGraduations.itemsCount
                    Text {
                        text : (index * 5).toString()
                        color: appSettings.colorSettings.lightColor
                        font.family: appSettings.fontSettings.textFontFamily
                        font.pointSize: appSettings.fontSettings.textPointSize

                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignBottom

                        width: parent.width
                        height: parent.height /graphGraduations.itemsCount
                        x : 0
                        y : parent.height- (index+1) * height + graphGraduations.offset
                    }

                }
            }

        }


        MgInformationGroup {
            id : tripInfo
            x : 0
            y  : parent.height * 0.55
            width: parent.width
            height: parent.height * 0.3

            title: "Trip information"

            items: [
                MgInformationItemModel {
                    label:  "Cruise"
                    value:  car.cruise ? "On" : "Off"
                },
                MgInformationItemModel {
                    label: "Av. Km/h"
                    value: car.driveStatistics.meanSpeed | 0
                },
                MgInformationItemModel {
                    label: "Dist. Km"
                    value: car.drivenDistance.toFixed(1)
                },
                MgInformationItemModel {
                    label: "Av. l/100Km"
                    value: car.driveStatistics.meanFuelConsumption.toFixed(1)
                }

            ]
            labelWidthRatio: 0.7
        }



    }


}
