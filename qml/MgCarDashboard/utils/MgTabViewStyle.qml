import QtQuick 2.0
import QtQuick.Controls.Styles 1.1
import QtGraphicalEffects 1.0

TabViewStyle {

    property int tabHeight
    property int tabsCount
    property int tabViewWidth
    property var icons
//private:

    property int __tabWidth : tabViewWidth  / tabsCount
    property int __lastTabWidth : tabViewWidth - (tabsCount-1) * __tabWidth +3

    property color __outlineColor: "#76E4F5"


    tab: Rectangle {
        anchors.margins: 50


        function isLastTab()
        {
            return styleData.index === (style.tabsCount- 1);
        }

        property var selectedGradient : Gradient {
            GradientStop {position: 0  ;color: Qt.rgba(0.5,0.5,0.8,1)}
            GradientStop {position: 0.5;color: Qt.rgba(0.2,0.2,0.8,1)}
            GradientStop {position: 1  ;color: Qt.rgba(0.2,0.2,0.8,1)}

        }

        property var unselectedGradient : Gradient {
            GradientStop {position: 0  ;color: Qt.rgba(0.4,0.4,0.4,1)}
            GradientStop {position: 0.5;color: Qt.rgba(0.2,0.2,0.2,1)}
            GradientStop {position: 1  ;color: Qt.rgba(0.2,0.2,0.2,1)}

        }

        gradient: styleData.selected ? selectedGradient : unselectedGradient
        implicitWidth: isLastTab() ? __lastTabWidth :  __tabWidth
        implicitHeight:tabHeight

        border.color: Qt.rgba(0.2,0.2,0.2,1)
        border.width: 1

        Text {
            id: text
            anchors.centerIn: parent
            text: styleData.title
            color:  "white"
        }

        Rectangle {
            id  : header
            x : 0
            y : 0
            width: parent.width
            height: parent.height * 0.06
            color: __outlineColor
        }
        Rectangle {
            id  : visibleRect
            x : 0
            y : parent.height * 0.9
            width: parent.width
            height: parent.height * 0.06
            visible: styleData.selected
            color: __outlineColor
        }
    }
}
