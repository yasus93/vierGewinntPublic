import QtQuick 2.11
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import QtQuick.Window 2.2

ApplicationWindow {
    property alias changePlayerAction: changePlayerAction
    property alias startNewGame : startNewGame
    property alias timer: timer
    property alias linGrad: linGrad

    id: applicationWindow
    visible: true

    minimumWidth: 1120
    minimumHeight: 840
    maximumHeight: 840
    maximumWidth: 1120

    title: qsTr("4Gewinnt")

    Timer {
            id: timer
        }

    LinearGradient {
        id: linGrad
        anchors.fill: parent
        gradient: Gradient {
            GradientStop {
                position: 0.25
                color: "#000000"
            }
            GradientStop {
                position: 0.67
                color: "#353636"
            }
            GradientStop {
                position: 1
                color: "#8A8C8C"
            }
        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Game")
            Action {
                id: startNewGame
                text: qsTr("&Restart")
                enabled: false
                onTriggered: glPage.myGlItem.newGame(glPage.player1.text, glPage.player2.text)


            }
            Action {
                id: changePlayerAction
                text: qsTr("&Change Players")
                enabled: false
                onTriggered: glPage.warning.open()
            }
            MenuSeparator { }
            Action { text: qsTr("&Quit")
                onTriggered: applicationWindow.close()
            }
        }
        Menu {
            title: qsTr("&Theme")
            Action { text: qsTr("Classic")
                onTriggered: glPage.myGlItem.changeTheme(2);
            }
            Action { text: qsTr("Stone")
                onTriggered: glPage.myGlItem.changeTheme(1);
            }
            Action { text: qsTr("Princess")
                onTriggered: glPage.myGlItem.changeTheme(0);
            }
        }
        Menu {
            title: qsTr("&Info")
            Action { text: qsTr("&About")
                onTriggered: popup.open()
            }
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent

        GlPage {
            id: glPage
            myGlItem.viewportY: applicationWindow.height - mapToItem(swipeView, x, y+ height).y
        }

        Popup {
            id: popup
            width: applicationWindow.width
            height: 180
            x: (parent.width - width) / 2

            Text {
                id: name
                font.pointSize: 16
                text: qsTr("Entwickelt von Sven Alexander Weikert und Yasin Demirbas\nunter Zuhilfenahme der zur Verfügung gestellten Klassen von\nWalter Roth.\n\nBitte drücken Sie Esc oder klicken Sie mit der Maus außerhalb\ndes Popups um es zu schließen.")
            }
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        }
    }
}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
