import QtQuick 2.9
import QtQuick.Controls 2.2
import GlComponents 1.0

Item {
    property alias myGlItem: myGlItem
    property alias mouseArea: mouseArea

    Row {
        id: row1
        x: 135
        y: 48
        width: 370
        height: 56

        RoundButton {
            id: roundButton
            width: 50
            height: 50
            text: "+"
        }

        RoundButton {
            id: roundButton1
            width: 50
            height: 50
            text: "+"
            anchors.left: roundButton.right
            anchors.leftMargin: 3
        }

        RoundButton {
            id: roundButton2
            width: 50
            height: 50
            text: "+"
            anchors.left: roundButton1.right
            anchors.leftMargin: 3
        }

        RoundButton {
            id: roundButton3
            width: 50
            height: 50
            text: "+"
            anchors.left: roundButton2.right
            anchors.leftMargin: 3
        }

        RoundButton {
            id: roundButton4
            width: 50
            height: 50
            text: "+"
            anchors.left: roundButton3.right
            anchors.leftMargin: 3
        }

        RoundButton {
            id: roundButton5
            width: 50
            height: 50
            text: "+"
            anchors.left: roundButton4.right
            anchors.leftMargin: 3
        }

        RoundButton {
            id: roundButton6
            width: 50
            height: 50
            text: "+"
            anchors.left: roundButton5.right
            anchors.leftMargin: 3
        }
    }

    MyGlItem {
        id: myGlItem
// @disable-check M16
        anchors.fill: parent
        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }

        Row {
            id: row
            x: 150
            y: 289
            width: 228
            height: 42
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 22
        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
