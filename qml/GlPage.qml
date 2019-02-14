import QtQuick 2.11
import GlComponents 1.0


GlPageForm {

    roundButton0.onClicked: myGlItem.insertDisc(roundButton0.x, roundButton0.y);
    roundButton1.onClicked: myGlItem.insertDisc(roundButton0.x, roundButton0.y);
    roundButton2.onClicked: myGlItem.insertDisc(roundButton0.x, roundButton0.y);
    roundButton3.onClicked: myGlItem.insertDisc(roundButton0.x, roundButton0.y);
    roundButton4.onClicked: myGlItem.insertDisc(roundButton0.x, roundButton0.y);
    roundButton5.onClicked: myGlItem.insertDisc(roundButton0.x, roundButton0.y);
    roundButton6.onClicked: myGlItem.insertDisc(roundButton0.x, roundButton0.y);

    mouseArea.onClicked:{
    console.log("X:" + mouse.x + " Y:" + mouse.y)
    myGlItem.doMouseClick(mouse.x, mouse.y)
}

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
