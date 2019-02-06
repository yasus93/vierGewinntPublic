import QtQuick 2.11
import GlComponents 1.0


GlPageForm {
    buttonRight.onClicked: myGlItem.toggleMove();
    buttonLeft.onClicked: myGlItem.toggleUp();

    mouseArea.onClicked:
       myGlItem.onMouseClicked(mouse.x, mouse.y);

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
