import QtQuick 2.9
import QtQuick.Controls 2.2

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        GlPage {
            //myGlItem.viewportX: mapToItem(swipeView, x, y + height).x
            myGlItem.viewportY: applicationWindow.height - mapToItem(swipeView, x, y+ height).y
        }


    }


    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            id: button1
            text: qsTr("Page 1")
        }
        TabButton {
            id: button2
            text: qsTr("Page 2")
        }
    }

}
