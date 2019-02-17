#include "myglitem.h"
#include "glitem.h"
#include "glpoint.h"
#include <QVector3D>
#include "glmouseray.h"

MyGlItem::MyGlItem() : GLItem()
{
    m_backgroundColor = GLColorRgba::clBlack;
    m_drawAxes = false;
    m_activatePaintAfterQml = true;
    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    m_eye = QVector3D(-30.0f, 10.0f, 0.0f);
    m_eye*=0.6f;
    m_lightDirection = QVector3D(-50.0f, 10.0f, 0.0f);

    m_blender = new GLBody("4Gewinnt");
    QStringList *texturen = new QStringList();
    texturen->append(":/textures/TexturesCom_FabricPlain0030_S.jpg");
    texturen->append(":/textures/TexturesCom_Fiberglass0027_S.jpg");
    texturen->append(":/textures/TexturesCom_Plastic0074_S.jpg");

    m_blender->setTextureFiles(*texturen);
}

void MyGlItem::newGame()
{
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
}

void MyGlItem::changeTheme(int theme)
{
    m_blender->setActiveTextureIndex(theme);
    currentTheme = theme;
    switch (currentTheme)
    {
    case 0:
    {
        for(int i = 0; i < redDiscs.size(); i++)
        {
            redDiscs[i]->setColor(GLColorRgba::clCyan);
        }
        for(int i = 0; i < yellowDiscs.size(); i++)
        {
            yellowDiscs[i]->setColor(GLColorRgba::clWhite);
        }
    }
        break;
    case 1:
    {
        for(int i = 0; i < redDiscs.size(); i++)
        {
            redDiscs[i]->setColor(GLColorRgba::clGreen);
        }
        for(int i = 0; i < yellowDiscs.size(); i++)
        {
            yellowDiscs[i]->setColor(GLColorRgba::clMagenta);
        }
    }
        break;
    case 2:
    {
        for(int i = 0; i < redDiscs.size(); i++)
        {
            redDiscs[i]->setColor(GLColorRgba::clRed);
        }
        for(int i = 0; i < yellowDiscs.size(); i++)
        {
            yellowDiscs[i]->setColor(GLColorRgba::clYellow);
        }
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
            switch (currentTheme) {
            case 0: color = GLColorRgba::clCyan;
                break;
            case 1: color = GLColorRgba::clGreen;
                break;
            case 2: color = GLColorRgba::clRed;
                break;
            }
        }
        else {
            switch (currentTheme) {
            case 0: color = GLColorRgba::clWhite;
                break;
            case 1: color = GLColorRgba::clMagenta;
                break;
            case 2: color = GLColorRgba::clYellow;
                break;
            }
        }

        GLDisc *insert = new GLDisc("", QPoint(buttonNumber, position), 0.75f, color, "", 0.5f, 30);
        insert->setCenter(field->fieldToPosition(QPoint(buttonNumber, position)));
        insert->makeSurface();
        insert->rotateModelPoints(v_XYZ, v_X, 180.0f);
        insert->move(QVector3D(1.95f, -2.2f, -2.5f));

        switch (currentTheme) {
        case 0: {
            if(color == GLColorRgba::clCyan)
            {
                redDiscs.append(insert);
            }
            else {
                yellowDiscs.append(insert);
            }
        }
            break;
        case 1: {
            if(color == GLColorRgba::clGreen)
            {
                redDiscs.append(insert);
            }
            else {
                yellowDiscs.append(insert);
            }
        }
            break;
        case 2: {
            if(color == GLColorRgba::clRed)
            {
                redDiscs.append(insert);
            }
            else {
                yellowDiscs.append(insert);
            }
        }
            break;
        }


        totalDiscs++;
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
  {
      redDiscs[i]->draw(m_renderer);
  }
  for(int i = 0; i < yellowDiscs.size(); i++)
  {
      yellowDiscs[i]->draw(m_renderer);
  }

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
