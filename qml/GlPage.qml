import QtQuick 2.11
import GlComponents 1.0


GlPageForm {

    roundButton0.onClicked: myGlItem.insertDisc(0);
    roundButton1.onClicked: myGlItem.insertDisc(1);
    roundButton2.onClicked: myGlItem.insertDisc(2);
    roundButton3.onClicked: myGlItem.insertDisc(3);
    roundButton4.onClicked: myGlItem.insertDisc(4);
    roundButton5.onClicked: myGlItem.insertDisc(5);
    roundButton6.onClicked: myGlItem.insertDisc(6);

    mouseArea.onClicked:{
    console.log("X:" + mouse.x + " Y:" + mouse.y)
    myGlItem.doMouseClick(mouse.x, mouse.y)
}

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
