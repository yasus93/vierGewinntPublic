#include "myglitem.h"
#include "glitem.h"
#include "glpoint.h"
#include <QVector3D>
#include <QPropertyAnimation>
#include <QQuickWindow>
#include <iostream>



MyGlItem::MyGlItem() : GLItem()
{
    m_backgroundColor = GLColorRgba::clBlack;
    m_drawAxes = false;
    m_activatePaintAfterQml = true;
    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout,
            this, &MyGlItem::timerSlot);
    m_timer->start(30);

    m_eye = QVector3D(-30.0f, 10.0f, 0.0f);
    m_eye*=0.6f;
    m_lightDirection = QVector3D(-50.0f, 10.0f, 0.0f);

    m_blender = new GLBody("4Gewinnt");
    QStringList *texturen = new QStringList();
    texturen->append(":/textures/TexturesCom_PaperCloseup0017_M.jpg");
    texturen->append(":/textures/TexturesCom_Fiberglass0027_S.jpg");
    texturen->append(":/textures/TexturesCom_Plastic0074_S.jpg");
    m_blender->setTextureFiles(*texturen);

    messages = new QList<QString>();

    messages->append("It's your turn ");
    messages->append("Place your Disc ");
    messages->append("You're up next ");
    messages->append("Time for your next move ");

    m_nextResult.insert(0, 0);
    m_nextResult.insert(1, 0);

    //setNextResult(m_nextResult);

}

void MyGlItem::timerSlot()
{
    if (window())
        window()->update();
    update();
}
void MyGlItem::keyPressEvent(QKeyEvent *ev)
{
    if(!gameRunning){
        return;
    }
    switch (ev->text().toInt()) {
    case 1:
        insertDisc(0);
        break;
    case 2:
        insertDisc(1);
        break;
    case 3:
        insertDisc(2);
        break;
    case 4:
        insertDisc(3);
        break;
    case 5:
        insertDisc(4);
        break;
    case 6:
        insertDisc(5);
        break;
    case 7:
        insertDisc(6);
        break;
    default:
        break;
    }
}
void MyGlItem::resetScore()
{
    m_nextResult[0] = 0;
    m_nextResult[1] = 0;
    setNextResult(m_nextResult);
}

void MyGlItem::staticPlayers(QString p1, QString p2)
{
    m_staticPlayer1 = p1;
    m_staticPlayer2 = p2;
}

void MyGlItem::newGame(QString player1, QString player2)
{


    m_player1 = player1;
    m_player2 = player2;

    setNextPlayer("Please start " + m_player1);

    redDiscs.clear();
    yellowDiscs.clear();

    counter1 = 0;
    counter2 = 0;
    counter3 = 0;
    counter4 = 0;
    counter5 = 0;
    counter6 = 0;
    counter7 = 0;

    totalDiscs = 0;

    switch (currentTheme)
    {
        case 0: setNextColor("#ee7942");
            break;
        case 1:
            setNextColor("#6a8941");
            break;
        case 2:
            setNextColor("red");
            break;
    }
    gameRunning = true;
}

void MyGlItem::changeTheme(int theme)
{
    m_blender->setActiveTextureIndex(theme);
    currentTheme = theme;

    if(totalDiscs % 2 == 0)
        setNextPlayer(messages->at(rand()%messages->size()) + m_player1);
    else
        setNextPlayer(messages->at(rand()%messages->size()) + m_player2);

    switch (currentTheme)
    {
    case 0:
        {
            for(int i = 0; i < redDiscs.size(); i++)
                redDiscs[i]->setColor(cl_Sienna);

            for(int i = 0; i < yellowDiscs.size(); i++)
                yellowDiscs[i]->setColor(cl_Coral);

            if(totalDiscs % 2 == 0)
                setNextColor("#ee7942");
            else
                setNextColor("#f08080");
        }
        break;
    case 1:
        {
            for(int i = 0; i < redDiscs.size(); i++)
                redDiscs[i]->setColor(cl_Lime);
            for(int i = 0; i < yellowDiscs.size(); i++)
                yellowDiscs[i]->setColor(cl_Turquoise);

            if(totalDiscs % 2 == 0)
                setNextColor("#6a8941");
            else
                setNextColor("#377e7e");
        }
        break;
    case 2:
        {
            for(int i = 0; i < redDiscs.size(); i++)
                redDiscs[i]->setColor(cl_Red);
            for(int i = 0; i < yellowDiscs.size(); i++)
                yellowDiscs[i]->setColor(cl_Yellow);

            if(totalDiscs % 2 == 0)
                setNextColor("red");
            else
                setNextColor("yellow");
        }
        break;
    }
}

void MyGlItem::insertDisc(int buttonNumber)
{
    int position = 0;

    switch(buttonNumber)
    {
        case 0: position = counter1++;
            break;
        case 1: position = counter2++;
            break;
        case 2: position = counter3++;
            break;
        case 3: position = counter4++;
            break;
        case 4: position = counter5++;
            break;
        case 5: position = counter6++;
            break;
        case 6: position = counter7++;
            break;
    }

    if(position < 6)
    {
        if(totalDiscs % 2 == 0)
        {
            m_nextPlayer = messages->at(rand()% (messages->size()) ) + m_player2;

            switch (currentTheme)
            {
                case 0: color = cl_Sienna;
                        m_nextColor = "#f08080";
                    break;
                case 1: color = cl_Lime;
                        m_nextColor = "#377e7e";
                    break;
                case 2: color = cl_Red;
                        m_nextColor = "yellow";
                    break;
            }
        }
        else
        {
            m_nextPlayer = messages->at(rand()% (messages->size())) + m_player1;

            switch (currentTheme)
            {
                case 0: color = cl_Coral;
                        m_nextColor = "#ee7942";
                    break;
                case 1: color = cl_Turquoise;
                        m_nextColor = "#6a8941";
                    break;
                case 2: color = cl_Yellow;
                        m_nextColor = "red";
                    break;
            }
        }

        GLDisc *insert = new GLDisc("", 8*(6 - position),QPoint(buttonNumber, position), 0.75f, color, "", 0.5f, 30);
        insert->setCenter(field->fieldToPosition(QPoint(buttonNumber, 6)));

        insert->makeSurface();
        insert->rotateModelPoints(v_XYZ, v_X, 180.0f);
        insert->move(QVector3D(1.95f, -2.2f, -2.5f));

        switch (currentTheme)
        {
            case 0:
            {
                if(color == cl_Sienna)
                    redDiscs.append(insert);
                else
                    yellowDiscs.append(insert);
            }
                break;
            case 1:
            {
                if(color == cl_Lime)
                    redDiscs.append(insert);
                else
                    yellowDiscs.append(insert);

            }
                break;
            case 2:
            {
                if(color == cl_Red)
                    redDiscs.append(insert);
                else
                    yellowDiscs.append(insert);

            }
                break;
        }

        totalDiscs++;

        if(redWins()){
            gameRunning = false;
            qDebug() << "red wins" << endl;
            setNextPlayer(m_player1+" Wins");

            m_nextOrder.clear();
            m_nextOrder.insert(0, m_player2);
            m_nextOrder.insert(1, m_player1);

            setNextOrder(m_nextOrder);

            if(m_staticPlayer1 == m_player1)
            {
                m_nextResult[0]++;
            }
            else{
                m_nextResult[1]++;
            }


            setNextResult(m_nextResult);
        }
        else if(yellowWins()){
            gameRunning = false;
            qDebug() << "yellow wins" << endl;
            setNextPlayer(m_player2+" Wins");

            m_nextOrder.clear();
            m_nextOrder.insert(0, m_player1);
            m_nextOrder.insert(1, m_player2);

            setNextOrder(m_nextOrder);

            if(m_staticPlayer2 == m_player2)
            {
                m_nextResult[1]++;
            }
            else{
                m_nextResult[0]++;
            }
            setNextResult(m_nextResult);
        }
        else if(totalDiscs == 42){
            setNextPlayer("It's a tie.");
            m_nextOrder.clear();
            m_nextOrder.insert(0, m_player1);
            m_nextOrder.insert(1, m_player2);

            setNextOrder(m_nextOrder);

            setNextResult(m_nextResult);
        }
        else {
            setNextPlayer(m_nextPlayer);
            setNextColor(m_nextColor);
        }
    }

}

void MyGlItem::doMouseClick(int x, int y)
{
    qDebug()<< x << y << endl;
}

void MyGlItem::paintOnTopOfQmlScene()
{
  m_blender->draw(m_renderer, false);

  for (int i = 0; i < redDiscs.size(); i++)
    redDiscs[i]->draw(m_renderer, false);

  for(int i = 0; i < yellowDiscs.size(); i++)
    yellowDiscs[i]->draw(m_renderer, false);

  //field->draw(m_renderer, false);

}

void MyGlItem::paintUnderQmlScene()
{
    //qDebug()<<"Overridden paintUnder was called";
}

void MyGlItem::setupGeometry()
{
   GLItem::setupGeometry();

   m_blender->readBinaryModelFile(":/obj/spielfeld.dat");
   m_blender->move(QVector3D(0.0f, -2.0f, 0.0f));

   field = new Board();
   field->makeSurface();
   field->rotateModelPoints(v_XYZ, v_Y, -50.0f);
   field->move(QVector3D(-1.0f, -2.0f, -0.25f));

}
bool MyGlItem::redWins(){
    return redHasHorizontal() || redHasVertical() || redHasDiagonal();
}
bool MyGlItem::yellowWins(){
    return yellowHasHorizontal() || yellowHasVertical() || yellowHasDiagonal();
}
bool MyGlItem::redHasHorizontal(){
    int xCoord[7] = {10,10,10,10,10,10,10};
    int c = 0;
    for(int hoehe = 0; hoehe<7;hoehe++){
        for(int i = 0; i<redDiscs.size(); i++){
            if(redDiscs[i]->getFieldCoord().y() == hoehe){
                xCoord[c] = redDiscs[i]->getFieldCoord().x();
                c++;
            }
        }
        c = 0;
        std::sort(xCoord, xCoord+7);

        for(int i = 0; i<=3; i++){
            if(xCoord[i] == 0 && xCoord[i+1] == 1 && xCoord[i+2] == 2 && xCoord[i+3] == 3){
                markWinnerHorizontal(redDiscs, 0, 3, hoehe);
                return true;
            }
            if(xCoord[i] == 1 && xCoord[i+1] == 2 && xCoord[i+2] == 3 && xCoord[i+3] == 4){
                markWinnerHorizontal(redDiscs, 1, 4, hoehe);
                return true;
            }
            if(xCoord[i] == 2 && xCoord[i+1] == 3 && xCoord[i+2] == 4 && xCoord[i+3] == 5){
                markWinnerHorizontal(redDiscs, 2, 5, hoehe);
                return true;
            }
            if(xCoord[i] == 3 && xCoord[i+1] == 4 && xCoord[i+2] == 5 && xCoord[i+3] == 6){
                markWinnerHorizontal(redDiscs, 3, 6, hoehe);
                return true;
            }
        }
        for(int i = 0; i<7; i++){
            xCoord[i] = 10;
        }

    }
    return false;
}

bool MyGlItem::yellowHasHorizontal(){
    int xCoord[7] = {10,10,10,10,10,10,10};
    int c = 0;
    for(int hoehe = 0; hoehe<7;hoehe++){
        for(int i = 0; i<yellowDiscs.size(); i++){
            if(yellowDiscs[i]->getFieldCoord().y() == hoehe){
                xCoord[c] = yellowDiscs[i]->getFieldCoord().x();
                c++;
            }
        }
        c = 0;
        std::sort(xCoord, xCoord+7);
        for(int i = 0; i<=3; i++){
            if(xCoord[i] == 0 && xCoord[i+1] == 1 && xCoord[i+2] == 2 && xCoord[i+3] == 3){
                markWinnerHorizontal(yellowDiscs, 0, 3, hoehe);
                return true;
            }
            if(xCoord[i] == 1 && xCoord[i+1] == 2 && xCoord[i+2] == 3 && xCoord[i+3] == 4){
                markWinnerHorizontal(yellowDiscs, 1, 4, hoehe);
                return true;
            }
            if(xCoord[i] == 2 && xCoord[i+1] == 3 && xCoord[i+2] == 4 && xCoord[i+3] == 5){
                markWinnerHorizontal(yellowDiscs, 2, 5, hoehe);
                return true;
            }
            if(xCoord[i] == 3 && xCoord[i+1] == 4 && xCoord[i+2] == 5 && xCoord[i+3] == 6){
                markWinnerHorizontal(yellowDiscs, 3, 6, hoehe);
                return true;
            }
        }
        for(int i = 0; i<7; i++){
            xCoord[i] = 10;
        }

    }
    return false;
}
bool MyGlItem::redHasVertical(){
    int yCoord[6] = {10,10,10,10,10,10};
    int c = 0;
    for(int breite = 0; breite<6;breite++){
        for(int i = 0; i<redDiscs.size(); i++){
            if(redDiscs[i]->getFieldCoord().x() == breite){
                yCoord[c] = redDiscs[i]->getFieldCoord().y();
                c++;
            }
        }
        c = 0;
        std::sort(yCoord, yCoord+6);
        for(int i = 0; i<=3; i++){
            if(yCoord[i] == 0 && yCoord[i+1] == 1 && yCoord[i+2] == 2 && yCoord[i+3] == 3){
                markWinnerVertical(redDiscs, 0,3,breite);
                return true;
            }
            if(yCoord[i] == 1 && yCoord[i+1] == 2 && yCoord[i+2] == 3 && yCoord[i+3] == 4){
                markWinnerVertical(redDiscs, 1,4,breite);
                return true;
            }
            if(yCoord[i] == 2 && yCoord[i+1] == 3 && yCoord[i+2] == 4 && yCoord[i+3] == 5){
                markWinnerVertical(redDiscs, 2,5,breite);
                return true;
            }

        }
        for(int i = 0; i<6; i++){
            yCoord[i] = 10;
        }

    }
    return false;
}
bool MyGlItem::yellowHasVertical(){
    int yCoord[6] = {10,10,10,10,10,10};
    int c = 0;
    for(int breite = 0; breite<6;breite++){
        for(int i = 0; i<yellowDiscs.size(); i++){
            if(yellowDiscs[i]->getFieldCoord().x() == breite){
                yCoord[c] = yellowDiscs[i]->getFieldCoord().y();
                c++;
            }
        }
        c = 0;
        std::sort(yCoord, yCoord+6);

        for(int i = 0; i<=3; i++){
            if(yCoord[i] == 0 && yCoord[i+1] == 1 && yCoord[i+2] == 2 && yCoord[i+3] == 3){
                markWinnerVertical(yellowDiscs, 0,3,breite);
                return true;
            }
            if(yCoord[i] == 1 && yCoord[i+1] == 2 && yCoord[i+2] == 3 && yCoord[i+3] == 4){
                markWinnerVertical(yellowDiscs, 1,4,breite);
                return true;
            }
            if(yCoord[i] == 2 && yCoord[i+1] == 3 && yCoord[i+2] == 4 && yCoord[i+3] == 5){
                markWinnerVertical(yellowDiscs, 2,5,breite);
                return true;
            }

        }
        for(int i = 0; i<6; i++){
            yCoord[i] = 10;
        }
    }
    return false;
}

bool MyGlItem::redHasDiagonal(){
    int xyCoord[7][6];
    for(int i = 0; i<6;i++){
        for(int j = 0; j<7;j++){
            xyCoord[j][i] = -1;
        }
    }
    for(int i = 0; i<redDiscs.size(); i++){
        int x = redDiscs[i]->getFieldCoord().x();
        int y = redDiscs[i]->getFieldCoord().y();
        xyCoord[x][y] = i;
    }
    for(int x = 0; x<4; x++){
        for(int y = 0; y<3;y++){
            if(xyCoord[x][y] != -1 && xyCoord[x+1][y+1] != -1 && xyCoord[x+2][y+2] != -1 && xyCoord[x+3][y+3] != -1){
                redDiscs[xyCoord[x][y]]->setColor(cl_White);
                redDiscs[xyCoord[x+1][y+1]]->setColor(cl_White);
                redDiscs[xyCoord[x+2][y+2]]->setColor(cl_White);
                redDiscs[xyCoord[x+3][y+3]]->setColor(cl_White);
                return true;
            }
        }
    }
    for(int x = 0; x<4; x++){
        for(int y = 0; y<3;y++){
            if(xyCoord[x][y+3] != -1 && xyCoord[x+1][y+2] != -1 && xyCoord[x+2][y+1] != -1 && xyCoord[x+3][y] != -1){
                redDiscs[xyCoord[x][y+3]]->setColor(cl_White);
                redDiscs[xyCoord[x+1][y+2]]->setColor(cl_White);
                redDiscs[xyCoord[x+2][y+1]]->setColor(cl_White);
                redDiscs[xyCoord[x+3][y]]->setColor(cl_White);
                return true;
            }
        }
    }
    return false;
}
bool MyGlItem::yellowHasDiagonal(){
    int xyCoord[7][6];
    for(int i = 0; i<6;i++){
        for(int j = 0; j<7;j++){
            xyCoord[j][i] = -1;
        }
    }
    for(int i = 0; i<yellowDiscs.size(); i++){
        int x = yellowDiscs[i]->getFieldCoord().x();
        int y = yellowDiscs[i]->getFieldCoord().y();
        xyCoord[x][y] = i;
    }
    for(int x = 0; x<4; x++){
        for(int y = 0; y<3;y++){
            if(xyCoord[x][y] != -1 && xyCoord[x+1][y+1] != -1 && xyCoord[x+2][y+2] != -1 && xyCoord[x+3][y+3] != -1){
                yellowDiscs[xyCoord[x][y]]->setColor(cl_White);
                yellowDiscs[xyCoord[x+1][y+1]]->setColor(cl_White);
                yellowDiscs[xyCoord[x+2][y+2]]->setColor(cl_White);
                yellowDiscs[xyCoord[x+3][y+3]]->setColor(cl_White);
                return true;
            }
        }
    }
    for(int x = 0; x<4; x++){
        for(int y = 0; y<3;y++){
            if(xyCoord[x][y+3] != -1 && xyCoord[x+1][y+2] != -1 && xyCoord[x+2][y+1] != -1 && xyCoord[x+3][y] != -1){
                yellowDiscs[xyCoord[x][y+3]]->setColor(cl_White);
                yellowDiscs[xyCoord[x+1][y+2]]->setColor(cl_White);
                yellowDiscs[xyCoord[x+2][y+1]]->setColor(cl_White);
                yellowDiscs[xyCoord[x+3][y]]->setColor(cl_White);
                return true;
            }
        }
    }
    return false;


}
void MyGlItem::markWinnerHorizontal(QList<GLDisc *> disc, int minX, int maxX, int currentY){
    for(int i = 0; i<disc.size(); i++){
        if(disc[i]->getFieldCoord().y() == currentY){
            if(disc[i]->getFieldCoord().x() <= maxX && disc[i]->getFieldCoord().x() >= minX){
                disc[i]->setColor(cl_White);
            }
        }
    }
}
void MyGlItem::markWinnerVertical(QList<GLDisc *> disc, int minY, int maxY, int currentX){
    for(int i = 0; i<disc.size(); i++){
        if(disc[i]->getFieldCoord().x() == currentX){
            if(disc[i]->getFieldCoord().y() <= maxY && disc[i]->getFieldCoord().y() >= minY){
                disc[i]->setColor(cl_White);
            }
        }
    }
}



