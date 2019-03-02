import QtQuick 2.11
import QtQuick.Controls 2.4
import GlComponents 1.0
import QtQuick.Window 2.2


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

    property alias button: button
    property alias buttonRow: buttonRow
    property alias player:player
    property alias player1: player1
    property alias player2: player2
    property alias playerInput: playerInput
    property alias warning: warning
    property alias ok: ok
    property alias back: back
    property alias nextPlayer: nextPlayer
    property alias score1: score1
    property alias player1Label: player1Label
    property alias score2: score2
    property alias player2Label: player2Label
    property alias rectangle: rectangle
    property alias rectangle2: rectangle2

    MyGlItem {
        id: myGlItem

        width: applicationWindow.width
        height: applicationWindow.height
        z: -1
        anchors.fill: parent



        Rectangle {
            id: nextPlayer
            x: 0
            y: 0
            width: applicationWindow.width
            height:55
            color: "transparent"
            z: 2
            Text {
                id: player
                anchors.horizontalCenter: parent.horizontalCenter
                color: myGlItem.nextColor
                text: myGlItem.nextPlayer
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 26
                visible: false
            }

            Rectangle {
                id: rectangle
                x: 0
                y: 25
                width: 200
                height: 85
                color: "transparent"

                Label {
                    id: player1Label
                    x:  5
                    y: 10
                    width: contentWidth
                    height: contentHeight
                    horizontalAlignment: Text.AlignLeft
                    color: "white"
                    font.pointSize: 24

                }

                Label {
                    id: score1
                    x: 15
                    y: 50
                    width: contentWidth
                    height: contentHeight
                    horizontalAlignment: Text.AlignLeft

                    color: "white"
                    font.pointSize: 30
                }
            }

            Rectangle{
                id:rectangle2
                x: applicationWindow.width - rectangle2.width
                y: 25

                width:200
                height:85
                color: "transparent"

                Label {
                    id: player2Label
                    x: (rectangle2.width - player2Label.width) - 5
                    y: 10
                    width: contentWidth
                    height: contentHeight
                    color: "white"
                    font.pointSize: 24
                    horizontalAlignment: Text.AlignLeft
                }

                Label {
                    id: score2
                    x: (rectangle2.width - score2.width ) - 15
                    y: 50

                    width: contentWidth
                    height: contentHeight

                    horizontalAlignment: Text.AlignRight


                    color: "white"
                    font.pointSize: 30
                }

            }


        }
        MouseArea {
            id: mouseArea
            anchors.topMargin: 0
            z: 1
            anchors.fill: parent

            Popup {
                id: warning

                width:applicationWindow.width
                height: 180

                background: Rectangle {
                    color: "black"
                }

                Text {
                    x: applicationWindow.width / 4.0
                    y: 70
                    width: applicationWindow.width
                    height: 100
                    font.pointSize: 16
                    color: "red"
                    text: qsTr("Warning, this will reset your current game")
                }

                Button {
                    id: back
                    x: applicationWindow.width / 1.5
                    y: 40
                    text: qsTr("Continue game")

                }
                Button {
                    id: ok
                    x: applicationWindow.width / 1.5
                    y: 100
                    text: qsTr("I'm sure")
                }
            }

            Row {
                id: buttonRow
                x: 0
                y: myGlItem.height /8
                width: parent.width / 2.0
                height: buttonRow.width / 7.0
                z: 1
                anchors.horizontalCenter: parent.horizontalCenter
                visible: false

                RoundButton {
                    id: roundButton0
                    width: parent.width / 7.0
                    height: parent.height
                    text: "+"
                    font.pointSize: 16
                    font.bold: true
                }

                RoundButton {
                    id: roundButton1
                    width: parent.width / 7.0
                    height: parent.height
                    text: "+"
                    font.pointSize: 16
                    font.bold: true
                }

                RoundButton {
                    id: roundButton2
                    width: parent.width / 7.0
                    height: parent.height
                    text: "+"
                    font.pointSize: 16
                    font.bold: true
                }

                RoundButton {
                    id: roundButton3
                    width: parent.width / 7.0
                    height: parent.height
                    text: "+"
                    font.pointSize: 16
                    font.bold: true
                }

                RoundButton {
                    id: roundButton4
                    width: parent.width / 7.0
                    height: parent.height
                    text: "+"
                    font.pointSize: 16
                    font.bold: true
                }

                RoundButton {
                    id: roundButton5
                    width: parent.width / 7.0
                    height: parent.height
                    text: "+"
                    font.pointSize: 16
                    font.bold: true
                }

                RoundButton {
                    id: roundButton6
                    width: parent.width / 7.0
                    height: parent.height
                    text: "+"
                    font.pointSize: 16
                    font.bold: true
                }
            }

            Rectangle {
                id: playerInput
                x:0
                y:50
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"
                width: 320
                height: 116
                z: 2

                TextField {
                    id: player1
                    x: 110
                    y: 6
                    width: 200
                    height: 27
                    placeholderText: qsTr("Please enter your name player 1")
                    font.pixelSize: 12
                    activeFocusOnTab: true
                    selectByMouse: true
                    validator: RegExpValidator {
                        regExp: /[A-Za-z]{3,15}/
                    }
                }

                Label{
                    id: element
                    x: 8
                    y: 6
                    color:"white"
                    width: 87
                    height: 24
                    text: qsTr("Player 1:")
                    font.pixelSize: 16
                }

                TextField {
                    id: player2
                    x: 110
                    y: 39
                    width: 200
                    height: 25
                    placeholderText: qsTr("Please enter your name player 2")
                    font.pixelSize: 12
                    activeFocusOnTab: true
                    selectByMouse: true
                    validator: RegExpValidator {
                        regExp: /[A-Za-z]{3,15}/
                    }

                }

                Label {
                    id: element1
                    x: 8
                    y: 39
                    color: "white"
                    width: 87
                    height: 24
                    text: qsTr("Player 2:")
                    font.pixelSize: 16
                }

                Button {
                    id: button
                    x: 110
                    y: 70
                    text: qsTr("Start Game")
                    enabled: player1.acceptableInput && player2.acceptableInput

                }

            }
        }


    }
}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
