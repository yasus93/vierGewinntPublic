import QtQuick 2.11
import GlComponents 1.0


GlPageForm {

    roundButton0.onClicked: myGlItem.insertDisc(roundButton0.x, 0);
    roundButton1.onClicked: myGlItem.insertDisc(roundButton1.x, 1);
    roundButton2.onClicked: myGlItem.insertDisc(roundButton2.x, 2);
    roundButton3.onClicked: myGlItem.insertDisc(roundButton3.x, 3);
    roundButton4.onClicked: myGlItem.insertDisc(roundButton4.x, 4);
    roundButton5.onClicked: myGlItem.insertDisc(roundButton5.x, 5);
    roundButton6.onClicked: myGlItem.insertDisc(roundButton6.x, 6);

    mouseArea.onClicked:{
    console.log("X:" + mouse.x + " Y:" + mouse.y)
    myGlItem.doMouseClick(mouse.x, mouse.y)
}

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
