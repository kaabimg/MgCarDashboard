import QtQuick 2.0

Item {

    id : root

    property real barWidthRatio : 0.15
    property int visibleIndex: -1

//private:

    function showTab(index)
    {
        visibleIndex = index;
    }

}
