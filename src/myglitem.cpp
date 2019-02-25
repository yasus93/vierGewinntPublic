#include "myglitem.h"
#include "glitem.h"
#include "glpoint.h"
#include <QVector3D>
#include <QPropertyAnimation>
#include <QQuickWindow>


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
}

void MyGlItem::timerSlot()
{
    if (window())
        window()->update();
    update();
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

        setNextPlayer(m_nextPlayer);
        setNextColor(m_nextColor);
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
