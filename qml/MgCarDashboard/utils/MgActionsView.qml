import QtQuick 2.2
import QtGraphicalEffects 1.0
import "mgactionsviewutils.js" as Utils
import Mg 1.0

Item {

    id : root

    property list<MgAction> actions

    property color actionFillColor : "#56C4E8"
    property color actionBorderColor : "#A1A1A1"
    property color actionTextColor : "#98CBED"
    property color actionHighlightColor : "#F5F5F5"
    property color actionsCircleColor : "#56C4E8"
    property real actionsOpacity : 0.4

    property real lineCircleRadius : Math.min(width,height)/150
    property int highlightLineWidth : 3



//private:
    anchors.fill : parent

    property bool isInPressAndHold_ : false

    property int cX_ : touchArea.mouseX
    property int cY_ : touchArea.mouseY

    property int drawRadius_ : 0
    property int actionRadius_ : actionsCircleRadius_ / 8
    property int currentPositionRadius_ : actionsCircleRadius_ / 10

    property int xCenter_ : width/2
    property int yCenter_ : height/2

    property int actionsCircleRadius_: Math.min(xCenter_,yCenter_) * 0.8

    property int selectedActionIndex_ : 0

    state : "invisible"

    property var actionsRelativePositions_

    Component.onCompleted: {
        Utils.calculateActionsPositions();
    }


    states: [
        State {
            name: "invisible"
            PropertyChanges {
                target: root
                drawRadius_ : 0
                isInPressAndHold_ : false
            }
        },
        State {
            name: "visible"
            PropertyChanges {
                target: root
                drawRadius_ : actionsCircleRadius_
                isInPressAndHold_ : true
            }
        }
    ]

    transitions: Transition {
        from: "invisible"
        to: "visible"
        reversible: true
        NumberAnimation { properties: "drawRadius_"; duration: 500; easing.type: Easing.Linear }
    }




    onDrawRadius_Changed:  canvas.requestPaint()

    onCX_Changed: tryToUpdateCanvas()
    onCY_Changed: tryToUpdateCanvas()



    function tryToStart()
    {
        var distance = Math.sqrt((cX_-xCenter_)*(cX_-xCenter_)+(cY_-yCenter_)*(cY_-yCenter_));
        if(distance<= actionsCircleRadius_*0.6 )
        {
            canvas.state = "lookingForAction";
            state = "visible";
        }
    }

    function tryToTriggerAction()
    {
        if(!isInPressAndHold_)
            return;
        selectedActionIndex_ = Utils.currentPositionAction();

        if(selectedActionIndex_ !=-1)
        {
            canvas.state = "selectingAction";
            actions[selectedActionIndex_].triggered();

        }
        else
        {
            canvas.state = "releasing";
        }


        state = "invisible";
    }

    function tryToUpdateCanvas()
    {
        if(!isInPressAndHold_)
            return;

        selectedActionIndex_ = Utils.currentPositionAction();

        if(selectedActionIndex_ !=-1)
        {
            canvas.state = "highlightingAction";
        }
        else
        {
            canvas.state = "lookingForAction";
        }

        canvas.requestPaint();
    }



    function calculateActionsPositions()
    {
        for(var i = 0;i<actions.length;i++)
        {

}
    }


    Canvas {
        id : canvas
        anchors.fill: parent

        visible: root.drawRadius_ != 0


//private:
        property bool drawActionsCircle_ : true
        property bool drawCurrentPosition_ : true
        property bool highlightCurrentAction_ : false
        property bool drawActions_ : true


        states: [

            State {
                name: "lookingForAction"
                PropertyChanges {
                    target: canvas
                    drawActionsCircle_ : true
                    drawCurrentPosition_ : true
                    highlightCurrentAction_ : false
                    drawActions_ : true

                }

            },

            State {
                name: "highlightingAction"
                PropertyChanges {
                    target: canvas
                    drawActionsCircle_ : false
                    drawCurrentPosition_ : false
                    highlightCurrentAction_ : true
                    drawActions_ : false


                }
            },
            State {
                name: "selectingAction"
                PropertyChanges {
                    target: canvas
                    drawActionsCircle_ : false
                    drawCurrentPosition_ : false
                    highlightCurrentAction_ : false
                    drawActions_ : false

                }
            },
            State {
                name: "releasing"
                PropertyChanges {
                    target: canvas
                    drawActionsCircle_ : true
                    drawCurrentPosition_ : false
                    highlightCurrentAction_ : false
                    drawActions_ : false
                }
            }
        ]

        onPaint: {
            var ctx = canvas.getContext('2d');
            ctx.clearRect (0, 0, width, height);          

            ctx.lineWidth = root.circleLineWidth
            if(drawActionsCircle_)
            {
                Utils.drawActionsCircle(ctx);
            }
            if(drawCurrentPosition_)
            {
                Utils.drawCurrentPosition(ctx);
            }

            if(highlightCurrentAction_)
            {
                Utils.highlightCurrentAction(ctx);
            }
            if(drawActions_)
            {
                Utils.drawActions(ctx);
            }
        }
    }



//    FastBlur {
//        anchors.fill: parent
//        source: canvas
//        radius: 50
//        visible :canvas.visible
//        z :1
//    }




    MouseArea {
        id : touchArea
        anchors.fill: parent
        onPressAndHold: root.tryToStart()
        onReleased:root.tryToTriggerAction()

    }


}
