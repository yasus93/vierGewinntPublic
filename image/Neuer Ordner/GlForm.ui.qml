import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import GlComponents 1.0

Item {

    property alias buttonRight : buttonRight
    property alias buttonLeft: buttonLeft
    property alias myGlItem : myGlItem
    MyGlItem {
        id: myGlItem
        anchors.fill: parent

        RowLayout {
            id: rowLayout
            x: 257
            y: 311
            width: 208
            height: 38
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: buttonLeft
                text: qsTr("Rotate left")
            }

            Button {
                id: buttonRight
                text: qsTr("Rotate right")
            }
        }
    }
}

/*##^## Designer {
    D{i:4;anchors_width:100;anchors_x:257}D{i:3;anchors_height:200;anchors_width:200;anchors_x:176;anchors_y:93}
}
 ##^##*/
