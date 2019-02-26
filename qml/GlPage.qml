import QtQuick 2.11
import GlComponents 1.0


GlPageForm {

    button.onClicked: {
        myGlItem.newGame(player1.text, player2.text)
        playerInput.visible = false

        buttonRow.visible = true
        player.visible = true
        startNewGame.enabled = true
        changePlayerAction.enabled = true
    }

    back.onClicked: warning.close()

    ok.onClicked: {
        //warning.visible = false
        warning.close()
        changePlayerAction.enabled = false
        startNewGame.enabled = false
        buttonRow.visible = false
        player.visible = false
        playerInput.visible = true
        player1.clear()
        player2.clear()
    }

    roundButton0.onClicked: myGlItem.insertDisc(0);
    roundButton1.onClicked: myGlItem.insertDisc(1);
    roundButton2.onClicked: myGlItem.insertDisc(2);
    roundButton3.onClicked: myGlItem.insertDisc(3);
    roundButton4.onClicked: myGlItem.insertDisc(4);
    roundButton5.onClicked: myGlItem.insertDisc(5);
    roundButton6.onClicked: myGlItem.insertDisc(6);

    mouseArea.onClicked:{
        myGlItem.doMouseClick(mouse.x, mouse.y)
    }
    myGlItem.onPlayerChanged: {
        player.text = next
    }
    myGlItem.onColorChanged: {
        player.color = color
    }

    myGlItem.onOrderChanged: {

        buttonRow.visible = false
        nextPlayer.y = 50
        player.text += "\n" + order[0] + " will start next\nNext game starts in 5 seconds ... "

        delay(5000, function (){
            buttonRow.visible = true
            nextPlayer.y = 0

            player1.text = order[0]
            player2.text = order[1]

            console.log(player1.text + player2.text)
            myGlItem.newGame(player1.text, player2.text)
        });


    }

    function delay(delayTime, cb) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
        return;
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
