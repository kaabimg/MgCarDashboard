import QtQuick 2.0
import QtGraphicalEffects 1.0
Item {
    id : root

    property int value : 0
    property color paintColor : "blue"
    property string unit :""
    property int digitsCount : 3

    //private:
    property int digitWidth: Math.min(height/2,width/5)
    Item{
        id : display

        anchors.fill : parent

        MgLcdDigit {
            id: digit1
            width:root.digitWidth
            height: root.digitWidth * 2
            anchors.right: digit2.left
            paintColor : root.paintColor
            digit: root.value /1000
            empty: digit == 0
        }

        MgLcdDigit {
            id: digit2
            width:root.digitWidth
            height: root.digitWidth * 2
            anchors.right: digit3.left
            paintColor : root.paintColor
            digit: (root.value /100 ) % 10
            empty: false
        }

        MgLcdDigit {
            id: digit3
            width:root.digitWidth
            height:root.digitWidth * 2
            anchors.right:digit4.left
            paintColor : root.paintColor
            digit: (root.value /10 ) % 10
            empty: false
        }

        MgLcdDigit {
            id: digit4
            width:root.digitWidth
            height: root.digitWidth * 2
            anchors.right: unit.left
            paintColor : root.paintColor
            digit: root.value  % 10
            empty : false
        }


        Canvas {
            id: unit
            width: root.digitWidth
            height: root.digitWidth
            anchors.right: parent.right


            onPaint: {

                var ctx = getContext("2d");

                var pointSize = 5;
                ctx.font = pointSize+"px sans-serif";
                var newPointSize = pointSize +1;
                for(var i=0;i<100;++i)
                {
                    newPointSize += 1;
                    ctx.font = newPointSize+"px sans-serif";
                    if(ctx.measureText(root.unit).width < width)
                        pointSize = newPointSize;
                    else
                        break;
                }
                ctx.font = pointSize+"px sans-serif";
                ctx.clearRect (0, 0, width, height);
                ctx.fillStyle = root.paintColor;
                ctx.fillText(root.unit,0,height* 0.6);

            }
        }

    }





    GaussianBlur {
        anchors.fill: parent
        radius: root.digitWidth / 8
        samples: 8
        source: display
    }



}
