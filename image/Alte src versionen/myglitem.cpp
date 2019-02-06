#include "myglitem.h"
#include "glitem.h"
#include "glpoint.h"

MyGlItem::MyGlItem() : GLItem()
{
    m_backgroundColor = GLColorRgba::clBlack;
    m_drawAxes = true;
    m_firstTrianglePoint = 0;
    m_lastTrianglePoint = 0;
    m_activatePaintAfterQml = true;
    initializeRenderer();
    this->setupGeometry();
    this->paintOnTopOfQmlScene();
}

void::MyGlItem::drawTriangles()
{
    if(m_lastTrianglePoint < m_firstTrianglePoint) //We have no axes
    {
        qDebug() << "GLItem::drawTriangles(): No data available.";
        return;
    }
    qDebug() << "drawTriangles was called and checked";


    m_renderer->setColorArrayEnabled(true);

    m_renderer->setLightingEnabled(false);
    int stride = sizeof(GLPoint);
    m_renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                       m_points[0].vertexPointer(), stride);
    m_renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                                       m_points[0].colorPointer(), stride);
qDebug() << "Bis hierhin läuft";
    glDrawArrays(GL_TRIANGLES, m_firstTrianglePoint, m_lastTrianglePoint - m_firstTrianglePoint + 1); //Triangle Coordinate
    m_renderer->disableAttributeArrays();
    //restore old settings
    m_renderer->setColorArrayEnabled(m_colorArrayEnabled);
    m_renderer->setLightingEnabled(m_lightingEnabled);


}

void MyGlItem::createTriangles()
{
    qDebug() << "create Triangles was called";
    m_firstTrianglePoint = m_points.size();
    qDebug() << m_firstTrianglePoint;
    m_points.append(GLPoint(QVector3D(0.0, 0.0, 0.0) , QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 0.0, 0.0), GLColorRgba::clRed));
    m_points.append(GLPoint(QVector3D(2.0, 0.0, 0.0) , QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 0.0, 0.0), GLColorRgba::clGreen));
    m_points.append(GLPoint(QVector3D(0.0, 2.0, 0.0) , QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 0.0, 0.0), GLColorRgba::clBlue));
    m_lastTrianglePoint = m_points.size()-1;
    qDebug() << m_lastTrianglePoint;
}

void MyGlItem::setupGeometry()
{
    GLItem::setupGeometry();
    createTriangles();
}
