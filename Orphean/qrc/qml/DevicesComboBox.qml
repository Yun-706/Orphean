import QtQuick 2.12
import QtQuick.Controls 2.15

ComboBox {
    id: comboBox

    property color bgColor: Qt.rgba(0.12,0.1,0.13,1)

    displayText: "音频设备：" + currentText

    background: Rectangle {
        color: Qt.rgba(0,0,0,0)
        border.color: "gray"
        border.width: 1
    }

    contentItem: Text {
        text: displayText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
    }

    indicator: Canvas {
        height: parent.height / 3
        width: parent.height / 2
        anchors.right: parent.right
        anchors.rightMargin: 7
        anchors.verticalCenter: parent.verticalCenter

        onPaint: {
            var ctx = getContext("2d");
            ctx.lineWidth = 2;
            ctx.strokeStyle = Qt.rgba(0.8,0.8,0.8,1);
            ctx.moveTo(0,0);
            ctx.lineTo(width/2, height);
            ctx.lineTo(width, 0);
            ctx.stroke();
        }
    }

    popup: Popup {
        y: parent.height
        width: parent.width
        implicitHeight: Math.min(comboList.contentHeight, 300)
        padding: 1

        background: Rectangle {
            anchors.fill: parent
            color: Qt.rgba(0.15,0.05,0.1,1)
            border.color: "black"
            border.width: 2
        }

        contentItem: ListView {
            id: comboList
            clip: true
            model: comboBox.delegateModel

            ScrollIndicator.vertical: ScrollIndicator {}

            highlight: Rectangle {
                anchors.fill: parent
                color: bgColor
                border.color: "black"
                border.width: 2
            }
        }
    }

    delegate: ItemDelegate {
        width: parent.width
        height: 30

        background: Rectangle {
            anchors.fill: parent
            color: hovered ? "white" : bgColor

            Rectangle {
                color: Qt.rgba(1,1,1,0.1)
                width: parent.width * 0.9 - 20
                height: 1
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        Text {
            text: modelData
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            color: hovered ? "black" : Qt.rgba(0.7,0.7,0.7,1)
        }

        onClicked: {
            currentIndex = index;
        }
    }
}
