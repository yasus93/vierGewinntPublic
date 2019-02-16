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
                y: 32
                width: 50
                height: 50
                text: "+"
            }

            RoundButton {
                id: roundButton5
                x: 398
                y: 32
                width: 50
                height: 50
                text: "+"
            }

            RoundButton {
                id: roundButton4
                x: 345
                y: 32
                width: 50
                height: 50
                text: "+"
            }

            RoundButton {
                id: roundButton3
                x: 292
                y: 32
                width: 50
                height: 50
                text: "+"
            }

            RoundButton {
                id: roundButton2
                x: 239
                y: 32
                width: 50
                height: 50
                text: "+"
            }

            RoundButton {
                id: roundButton1
                x: 186
                y: 32
                width: 50
                height: 50
                text: "+"
            }

            RoundButton {
                id: roundButton0
                x: 136
                y: 32
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
