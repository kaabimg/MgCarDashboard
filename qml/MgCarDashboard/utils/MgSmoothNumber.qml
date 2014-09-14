import QtQuick 2.0



QtObject {

    property real value: 0
    property alias duration: animation.duration
    property alias easing: animation.easing


    Behavior on value {
         SmoothedAnimation {
             id :animation
             velocity: 0.1
             duration: 700
             easing.type: Easing.Linear
         }
     }
}



