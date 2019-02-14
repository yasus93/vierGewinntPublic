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

    onlySetOnce = true;


    m_fovy         = 45.0f;
        m_aspect       =  1.0f;
        m_eye = QVector3D(-30.0f, 10.0f, 0.0f);
        m_eye*=0.6f;
        m_lightDirection = QVector3D(-50.0f, 10.0f, 0.0f);
        m_blender = new GLBody("4Gewinnt");
        m_blender->setTextureFile(":/textures/TexturesCom_Plastic0074_S.jpg");
        m_orthoMode    = false;
        m_orthoRange   = 1.0;
        m_mouseRay = nullptr;
}



void MyGlItem::paintOnTopOfQmlScene()
{
  m_blender->draw(m_renderer, false);
}


void MyGlItem::paintUnderQmlScene()
{
    //qDebug()<<"Overridden paintUnder was called";

}


void MyGlItem::setupGeometry()
{
    GLItem::setupGeometry();

   m_blender->readBinaryModelFile(":/obj/spielfeld.dat");
}
