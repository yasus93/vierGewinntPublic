#include "glmouseray.h"

GLMouseRay::GLMouseRay():GLBody("MouseRay")
{
    m_drawingMode = GL_LINES;
    m_color = cl_Red;
}

void GLMouseRay::makeSurface(QVector3D nah, QVector3D fern)
{
    GLBody::makeSurface(nullptr, nullptr);

    m_firstPoint = m_points->size();

     m_points->append(GLPoint(nah, v_XYZ, QVector3D(), GLColorRgba::clWhite));
     m_points->append(GLPoint(fern, v_XYZ, QVector3D(), GLColorRgba::clWhite));

     m_nextPoint = m_points->size();
}
