#include "glmouseray.h"
#include "gldefines.h"

GLMouseRay::GLMouseRay(const QString & name)
    :GLBody(name)
{
  m_color = GLColorRgba::clRed;
}

void GLMouseRay::setMousePosition(QPoint pos, GLESRenderer *renderer)
{
  if(!m_surfaceIsValid)
      makeSurface(nullptr, nullptr);
  renderer->calculateMousePoints((*m_points)[0].vertexPointer(), (*m_points)[1].vertexPointer(), pos);
  m_positionIsValid = true;
}

void GLMouseRay::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer)
{
  Q_UNUSED(pointContainer);
  Q_UNUSED(indexContainer);

  GLBody::makeSurface(nullptr, nullptr);
  m_firstPoint = static_cast<IndexType>(m_points->size());
  m_points->append(GLPoint(m_nearPoint, v_Z, v_Zero, m_color));
  m_points->append(GLPoint(m_farPoint, v_Z, v_Zero, m_color));
  m_nextPoint = static_cast<IndexType>(m_points->size());
}

void GLMouseRay::draw(GLESRenderer *renderer, bool useBuffers)
{
   Q_UNUSED(useBuffers);

   GLfloat oldLineWidth = 0.0;
   glGetFloatv(GL_LINE_WIDTH, &oldLineWidth);
   glLineWidth(3.0);
   setDrawingMode(GL_LINES);
   GLBody::draw(renderer, false);
   glLineWidth(oldLineWidth);

   GLfloat oldPointSize = 1.0f;
   glGetFloatv(GL_POINT_SIZE, &oldPointSize);
 //  glPointSize(5.0);
   setDrawingMode(GL_POINTS);
   GLBody::draw(renderer, false);
//   glPointSize(oldPointSize);
}
