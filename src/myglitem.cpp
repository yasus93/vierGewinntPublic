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

    m_eye = QVector3D(-30.0f, 0.0f, 0.0f);
    m_eye*=0.6f;
    m_lightDirection = QVector3D(-50.0f, 10.0f, 0.0f);

    m_blender = new GLBody("4Gewinnt");
    m_blender->setTextureFile(":/textures/TexturesCom_Plastic0074_S.jpg");
}

void MyGlItem::insertDisc(int x, int buttonNumber)
{
    int position;
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

    GLDisc *insert = new GLDisc(QPoint(x, buttonNumber), 0.75f, GLColorRgba::clRed, "", 0.5f, 30);
    insert->setCenter(field->fieldToPosition(QPoint(buttonNumber, position)));
    insert->makeSurface();
    insert->rotateModelPoints(v_XYZ, v_X, 180.0f);
    insert->move(QVector3D(1.95f, -0.2f, -2.5f));

    whiteDiscs.append(insert);
}

void MyGlItem::doMouseClick(int x, int y)
{
    qDebug()<< x << y << endl;
}

void MyGlItem::paintOnTopOfQmlScene()
{

  m_blender->draw(m_renderer, false);

  for (int i = 0; i < whiteDiscs.size(); i++)
  {
      whiteDiscs[i]->draw(m_renderer);
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

   field = new Board();
   field->makeSurface();
   field->rotateModelPoints(v_XYZ, v_Y, -50.0f);
   field->move(QVector3D(-1.0f, 0.0f, -0.25f));

}
