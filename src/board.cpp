#include "board.h"
#include "shaderdebugger.h"
#include "gldisc.h"

Board::Board()
    :GLBody("Board")
{
    m_center = QVector3D(0.0f, 0.0f, 0.0f);
    m_normal = v_Y;

    b_firstPoint = new QVector3D(-4.07698f, 4.79138f, -3.8186f);
    b_secondPoint = new QVector3D(-2.85293f, 4.79138f, -2.80426f);
    b_thirdPoint = new QVector3D(-4.07698f, 3.20417f, -3.8186f);

    deltaX = b_firstPoint->x() - b_secondPoint->x();
    deltaY = b_firstPoint->y() - b_thirdPoint->y();
    deltaZ = b_firstPoint->z() - b_secondPoint->z();

    setDrawingMode(GL_TRIANGLE_STRIP);
}
/**
  * Returns 3D position of field center. Field coordinates are from 0 to 7
  */
QVector3D Board::fieldToPosition(QPoint field)
{
    QVector3D move = QVector3D(field.y() * (-deltaY), deltaZ, field.x() * (-deltaY));

    return *b_firstPoint + move;
}

void Board::makeSurface(QVector<GLPoint> *pointContainer, QVector<IndexType> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    m_firstPoint = static_cast<GLushort>(m_points->size());
    m_firstIndex = static_cast<GLushort>(m_indices->size());

    QVector3D *vx = new QVector3D(deltaX, 0.0f, deltaZ);
    QVector3D *vy = new QVector3D(0.0f, deltaY, 0.0f);

    for(int i = 0; i < 8; i++)
    {
        for(int row = 0; row <7; row++)
        {
            QVector3D rowStart = *b_firstPoint - (row * *vy);
            for (int column = 0; column < 2; column++)
            {
                QVector3D vert = rowStart - (column * *vx);
                m_indices->append(static_cast<GLushort>(m_points->size()));
                m_points->append(GLPoint(vert));
            }
        }
        *b_firstPoint = *b_firstPoint - *vx;
    }
    m_nextPoint = static_cast<GLushort>(m_points->size());
    m_nextIndex = static_cast<GLushort>(m_indices->size());
}
