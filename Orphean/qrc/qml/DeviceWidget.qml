import QtQuick 2.12
import Orphean 1.0

Rectangle {

    Orphean {
        id: orphean
    }

    objectName: "DeviceWidget"
    width: 260
    height: 100
    color: Qt.rgba(0,0,0,0)
    border.color: Qt.rgba(1,1,1,1)
    border.width: 1

    property int xPosMax: parent.width - width
    property int yPosMax: parent.height - height

    onXPosMaxChanged: { posLimit() }
    onYPosMaxChanged: { posLimit() }

    function posLimit() {
        if (x < 0) x = 0;
        else if (x > xPosMax) x = xPosMax;
        if (y < 0) y = 0;
        else if (y > yPosMax) y = yPosMax;

        console.log(orphean.openInputDevice("hello"));
    }

    Text {
        id: title
        text: qsTr("请选择输入设备：")
        color: Qt.rgba(0.98, 0.98, 0.98, 1.0)
    }

    MouseArea {
        anchors.fill: parent
        property int pressMouseX
        property int pressMouseY
        property bool moving: false

        onPressed: {
            pressMouseX = mouseX
            pressMouseY = mouseY;
            moving = true;
        }

        onPositionChanged: {
            parent.x += mouseX - pressMouseX;
            parent.y += mouseY - pressMouseY;
            posLimit();
        }

        onReleased: {
            moving = false;
        }
    }


    DevicesComboBox {
        objectName: "DevicesComboBox"
        width: parent.width - 20
        height: 26
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
