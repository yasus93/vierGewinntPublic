import QtQuick 2.11
import QtQuick.Controls 2.4
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

            Row {
                id: row
                x: 162
                y: 51
                width: 317
                height: 46

                RoundButton {
                    id: roundButton0
                    width: 45
                    height: 45
                    text: "+"
                }

                RoundButton {
                    id: roundButton1
                    width: 45
                    height: 45
                    text: "+"
                }

                RoundButton {
                    id: roundButton2
                    width: 45
                    height: 45
                    text: "+"
                }

                RoundButton {
                    id: roundButton3
                    width: 45
                    height: 45
                    text: "+"
                }

                RoundButton {
                    id: roundButton4
                    width: 45
                    height: 45
                    text: "+"
                }

                RoundButton {
                    id: roundButton5
                    width: 45
                    height: 45
                    text: "+"
                }

                RoundButton {
                    id: roundButton6
                    width: 45
                    height: 45
                    text: "+"
                }
            }
        }
    }
}








/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
