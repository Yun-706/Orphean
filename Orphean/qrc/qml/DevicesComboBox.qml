import QtQuick 2.12
import QtQuick.Controls 2.15

ComboBox {
    id: comboBox

    property color bgColor: Qt.rgba(0.12,0.1,0.13,1)

    displayText: currentText

    background: Rectangle {
        color: Qt.rgba(0,0,0,0)
        border.color: "gray"
        border.width: 1
    }

    contentItem: Text {
        text: displayText
        clip: true
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.right: comboIndicator.left
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        color: "white"
        font.pixelSize: 10
    }

    indicator: Canvas {
        id: comboIndicator
        height: parent.height / 3
        width: parent.height / 2
        anchors.right: parent.right
        anchors.rightMargin: 7
        anchors.verticalCenter: parent.verticalCenter

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            ctx.lineWidth = parent.popup.visible ? 2 : 1;
            ctx.strokeStyle = parent.popup.visible ? Qt.rgba(1,1,0.7,1) : Qt.rgba(1,1,1,0.7);
            ctx.moveTo(0,0);
            ctx.lineTo(width/2, height);
            ctx.lineTo(width, 0);
            ctx.stroke();
        }
    }

    property int popupWidth

    function textWidth(txtWidth) {
        if (txtWidth > width) {
            if (txtWidth > popupWidth) {
                popupWidth = Math.min(txtWidth, 600);
            }
        }
        else {
            popupWidth = width;
        }
    }

    popup: Popup {
        y: parent.height
        width: popupWidth
        implicitHeight: Math.min(comboList.contentHeight, 300)
        padding: 1

        onVisibleChanged: {
            comboIndicator.requestPaint();
        }

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
        height: 30
        width: popupWidth
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
            clip: true
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            color: hovered ? "black" : Qt.rgba(0.7,0.7,0.7,1)

            Component.onCompleted: {
                textWidth(contentWidth + 15);
            }
        }

        onClicked: {
            currentIndex = index;
        }
    }
}
