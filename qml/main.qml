import QtQuick 2.11
import QtQuick.Controls 2.4

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("4Gewinnt")

    menuBar: MenuBar {
           Menu {
               title: qsTr("&File")
               Action {
                        text: qsTr("&New Game")
                        onTriggered: glPage.myGlItem.newGame()
               }

               MenuSeparator { }
               Action { text: qsTr("&Quit")
                        onTriggered: applicationWindow.close()
               }
           }
           Menu {
               title: qsTr("&Change Theme")
               Action { text: qsTr("Original")
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
               title: qsTr("&Help")
               Action { text: qsTr("&About")
                        onTriggered: aboutD
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


    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
