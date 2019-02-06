import QtQuick 2.9
import QtQuick.Controls 2.2
import GlComponents 1.0

Item {
    property alias myGlItem: myGlItem
    property alias mouseArea: mouseArea
   property alias buttonLeft: buttonLeft
    property alias buttonRight: buttonRight
    MyGlItem {
        id: myGlItem
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
