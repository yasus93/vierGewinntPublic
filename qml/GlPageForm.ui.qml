import QtQuick 2.9
import QtQuick.Controls 2.2
import GlComponents 1.0

Item {
    property alias myGlItem: myGlItem
    property alias mouseArea: mouseArea
    property alias roundButton3: roundButton3
    property alias roundButton4: roundButton4
    property alias roundButton5: roundButton5
    property alias roundButton6: roundButton6
    property alias roundButton2: roundButton2
    property alias roundButton1: roundButton1
    property alias roundButton0: roundButton0

    MyGlItem {
        id: myGlItem

        anchors.fill: parent
        MouseArea {
            id: mouseArea
            anchors.topMargin: 0
            z: 1
            anchors.fill: parent

            RoundButton {
                id: roundButton6
                x: 451
                y: 55
                width: 50
                height: 50
                text: "+"
                anchors.left: roundButton5.right
                anchors.leftMargin: 3
            }

            RoundButton {
                id: roundButton5
                x: 398
                y: 55
                width: 50
                height: 50
                text: "+"
                anchors.left: roundButton4.right
                anchors.leftMargin: 3
            }

            RoundButton {
                id: roundButton4
                x: 345
                y: 55
                width: 50
                height: 50
                text: "+"
                anchors.left: roundButton3.right
                anchors.leftMargin: 3
            }

            RoundButton {
                id: roundButton3
                x: 292
                y: 55
                width: 50
                height: 50
                text: "+"
                anchors.left: roundButton2.right
                anchors.leftMargin: 3
            }

            RoundButton {
                id: roundButton2
                x: 239
                y: 55
                width: 50
                height: 50
                text: "+"
                anchors.left: roundButton1.right
                anchors.leftMargin: 3
            }

            RoundButton {
                id: roundButton1
                x: 186
                y: 55
                width: 50
                height: 50
                text: "+"
                anchors.left: roundButton0.right
                anchors.leftMargin: 3
            }

            RoundButton {
                id: roundButton0
                x: 133
                y: 55
                width: 50
                height: 50
                text: "+"
            }






        }
    }
}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
