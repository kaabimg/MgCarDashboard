import QtQuick 2.0
import QtGraphicalEffects 1.0
import Mg 1.0

import "../utils"

Item {
    id : root
    property real diameter: 200


    MgDriveModeView {

        width: diameter * 0.4
        height: diameter * 0.08
        x : root.width * 0.5 - width/2
        y : root.height * 0.49 - height/2
        currentMode: car.driveMode

    }



    Item {
        id : graduations

        property real textRadius : 0.5 * 0.75

        function xPosition(angle) {
            return speedController.xPosition(
                        speedItemsBackground.width,
                        speedController.calculateProjectedAngle(angle),
                        speedItemsBackground.diameter * textRadius
                        );
        }

        function yPosition(angle) {
            return speedController.yPosition(
                        speedItemsBackground.height,
                        speedController.calculateProjectedAngle(angle),
                        speedItemsBackground.diameter *textRadius
                        );
        }

        property var speeds : [0,30,50,70,90,110,130,150,170]


        Repeater {
            model: graduations.speeds.length
            MgGaugeText {

                value: graduations.speeds[index]
                xCenter: graduations.xPosition(graduations.speeds[index])
                yCenter: graduations.yPosition(graduations.speeds[index])

                width: 50
                height: 50
                active:  speedController.currentValue >= graduations.speeds[index]
            }
        }
    }


    function innerDiskColor() {
        return car.rpmICE>0 ? appSettings.colorSettings.color2 : (car.rpmMG2 > 0 ? appSettings.colorSettings.color3 : appSettings.colorSettings.intermediaryColor) ;
    }

    property color _innerDiskColor : innerDiskColor()

    MgArcView {
        id : innerDisk
        diameter:  root.diameter
        anchors.fill: parent

        shadingMode : MgArcView.Glow
        pointsSize: 50
        innerRadius: 0.5
        outerRadius: 0.56
        color1 : _innerDiskColor

        startAngle:  Math.PI * 2
        endAngle: 0
        fullDisk : true


    }


    MgArcView {
        id : speedItemsBackground
        diameter: root.diameter
        anchors.fill: parent
        shadingMode: MgArcView.InnerRadiusToOuterRadiusExponentialGradient

        pointsSize: 50
        innerRadius: 0.6
        outerRadius: 0.95

        color1 : _innerDiskColor
        color2 : _innerDiskColor

        startAngle :  Math.PI * 2
        endAngle: 0
        fullDisk : true
    }


    //speed


    MgSmoothNumber {
        id : speed
        value : car.speed
    }

    MgGaugeController {
        id : speedController
        minValue: 0
        maxValue:170
        minAngle: Math.PI * 1.1
        maxAngle: -Math.PI * .1
        currentValue: speed.value
    }

    MgArcView {
        id : speedGaug1
        diameter: root.diameter
        anchors.fill: parent
        shadingMode: MgArcView.Glow
        pointsSize: 50
        innerRadius: 0.88
        outerRadius: 0.92
        color1 : appSettings.colorSettings.color1
        startAngle : speedController.minAngle
        endAngle: speedController.projectedAngle
    }

    MgArcView {
        id : speedGauge2
        diameter: root.diameter
        anchors.fill: parent
        shadingMode: MgArcView.Flat
        z: 1
        pointsSize: 50
        innerRadius: 0.605
        outerRadius: 0.89
        color1 : appSettings.colorSettings.color1
        opacity: 0.2
        startAngle : speedController.minAngle
        endAngle: speedController.projectedAngle
    }

    Item {
        id : speedText
        //private
        width: root.diameter * 0.2
        height:  root.diameter * 0.1
        x : root.width *0.5  - width *0.5
        y : root.height * 0.35

        Text {
            id : speedTextITem
            anchors.fill: parent
            text : (speed.value | 0).toString()
            color:  appSettings.colorSettings.color1
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: appSettings.fontSettings.speedGaugePointSize
            font.family: appSettings.fontSettings.speedGaugeFontFamily
        }
        Text {//unit
            anchors.left: speedTextITem.right
            y : speedTextITem.y
            width: speedTextITem.width
            height: speedTextITem.height
            text : "Km/h"
            color:  appSettings.colorSettings.color1
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pointSize: appSettings.fontSettings.speedGaugePointSize * 0.25
            font.family: appSettings.fontSettings.speedGaugeFontFamily
        }


    }


 //RPM

    Item {
        id : rpmItem
        anchors.fill: parent


        property real backgroungInnerRadius : 0.96
        property real backgroungOuterRadius: 1.1

        property real gaugeInnerRadius : 0.965
        property real gaugeOuterRadius: 1.095




        //ICE
        MgSmoothNumber {
            id : rpmICE
            value : car.rpmICE
        }
        MgGaugeController {
            id : rpmICEmController
            minValue: 0
            maxValue: 6000
            minAngle:  Math.PI * 1.5
            maxAngle:  Math.PI * .5
            currentValue: rpmICE.value
        }
        Item {
            id : rpmICEGauge
            anchors.fill : parent

            MgArcView {//backround
                id : rpmICEGaugeBackground
                diameter: root.diameter
                anchors.fill: parent
                shadingMode: MgArcView.InnerRadiusToOuterRadiusExponentialGradient
//                shadingMode: MgArcView.Flat
                pointsSize: 50
                innerRadius: rpmItem.backgroungInnerRadius
                outerRadius: rpmItem.backgroungOuterRadius
                color1 : appSettings.colorSettings.color2
                color2 : appSettings.colorSettings.color2
                startAngle : rpmICEmController.minAngle
                endAngle: rpmICEmController.maxAngle

            }
            MgArcView {//value
                id : rpmICEGaugeValue
                diameter: root.diameter
                anchors.fill: parent
                shadingMode: MgArcView.ThinGlow
                pointsSize: 30
                innerRadius: rpmItem.gaugeInnerRadius
                outerRadius: rpmItem.gaugeOuterRadius
                color1 : appSettings.colorSettings.color2
                startAngle : rpmICEmController.minAngle
                endAngle: rpmICEmController.projectedAngle
            }
        }




        //MG2
        MgSmoothNumber {
            id : rpmMG2
            value : car.rpmMG2
        }
        MgGaugeController {
            id : rmpMG2Controller
            minValue: 0
            maxValue: 6501
            minAngle: - Math.PI * 0.5
            maxAngle: Math.PI * 0.5
            currentValue: rpmMG2.value

        }
        Item {
            id : rpmMG2Gauge
            anchors.fill : parent

            MgArcView {//background
                id : rpmMG2GaugeBackground
                diameter: root.diameter
                anchors.fill: parent
                shadingMode: MgArcView.InnerRadiusToOuterRadiusExponentialGradient
                pointsSize: 50
                innerRadius: rpmItem.backgroungInnerRadius
                outerRadius: rpmItem.backgroungOuterRadius
                color1 : appSettings.colorSettings.color3
                color2 : appSettings.colorSettings.color3
                startAngle :  rmpMG2Controller.maxAngle
                endAngle: rmpMG2Controller.minAngle
            }
            MgArcView {//value
                id : rpmMG2GaugeValue
                diameter: root.diameter
                anchors.fill: parent
                shadingMode: MgArcView.ThinGlow
                pointsSize: 30
                innerRadius: rpmItem.gaugeInnerRadius
                outerRadius: rpmItem.gaugeOuterRadius
                color1 : appSettings.colorSettings.color3
                startAngle : rmpMG2Controller.projectedAngle
                endAngle: rmpMG2Controller.minAngle
            }
        }
    }




}
