import QtQuick 2.0
import QtQuick.Controls 1.1
import Mg 1.0
import "../utils"

Item {
    id : root


    MgPowerModeView {
        anchors.fill: parent
    }

/*
    Component.onCompleted: {
        meanTimer.start();
    }



    MgGraphView {
        id : fuelConsumptionGraph
        x : 0
        y : 0
        width: parent.width
        height: parent.height/2

        minY : 0
        maxY  : 300
        timeWindow : 5 * 60 * 1000
        graphPointsSize : 5 * 60 * 5

        graphColor : appSettings.colorSettings.color1
        fillColor: Qt.rgba(appSettings.colorSettings.color1.r,appSettings.colorSettings.color1.g,appSettings.colorSettings.color1.b,0.4)

        graphLineWidth :   1
        pointsProvider: MgPointsProvider {
            id : pointsProvider
            source: car
            targetProperty: "batteryVoltage"
            period: 200
        }


        Component.onCompleted: {
            pointsProvider.start();
        }

        Timer {
            id : meanTimer
            interval: 1000
            repeat: true
            onTriggered: {
                meanLineCanvas.requestPaint();
                //                meanGasConsumption.update();
            }


        }

        Rectangle{//background
            anchors.fill: parent
            color: appSettings.colorSettings.darkColor
            z : -1
        }



        Canvas {
            id  : meanLineCanvas
            anchors.fill: parent
            visible: false
            property color lineColor: appSettings.colorSettings.color2
            property real lineWidth : 3

            onPaint: {
                var ctx = getContext('2d');
                ctx.clearRect (0, 0, width, height);
                ctx.strokeStyle = lineColor;
                ctx.lineWidth = lineWidth;

                var y  = fuelConsumptionGraph.yToRelativePosition(pointsProvider.mean);
                ctx.beginPath();
                ctx.moveTo(0,y);
                ctx.lineTo(fuelConsumptionGraph.width,y);
                ctx.stroke();
                ctx.closePath();

            }
        }

    }


    MgGraphView {
        id : batteryGraph
        x : 0
        y : parent.height/2
        width: parent.width
        height: parent.height/2

        minY : 0
        maxY  : 500
        timeWindow : 5 * 60 * 1000
        graphPointsSize : 5 * 60 * 5

        graphColor : appSettings.colorSettings.color2
        fillColor: Qt.rgba(appSettings.colorSettings.color2.r,appSettings.colorSettings.color2.g,appSettings.colorSettings.color2.b,0.4)

        graphLineWidth :   1
        pointsProvider: MgPointsProvider {
            id : batteryCurrentPointsProvider
            source: car
            targetProperty: "batteryCurrent"
            period: 200
        }


        Component.onCompleted: {
            batteryCurrentPointsProvider.start();
        }





        Rectangle{//background
            anchors.fill: parent
            color: appSettings.colorSettings.darkColor
            z : -1
        }

    }



    MgInformationGroup {

        id : informationView
        width: parent.width * 0.2
        height: parent.height * 0.15

        x : parent.width - width - 10
        y : 10

        labelWidthRatio: 0.6

        items: [
            MgInformationItemModel {
                label: "Voltage (V)"
                value: car.batteryVoltage
                labelColor: appSettings.colorSettings.color1
                valueColor: appSettings.colorSettings.color1
            },
            MgInformationItemModel {
                label: "Current (A)"
                value: car.batteryCurrent
                labelColor: appSettings.colorSettings.color2
                valueColor: appSettings.colorSettings.color2

            }
        ]
    }


*/

}
