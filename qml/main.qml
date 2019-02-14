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

        GlPage {
            // @disable-check M18
            myGlItem.viewportY: applicationWindow.height - mapToItem(swipeView, x, y+ height).y
        }


    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
