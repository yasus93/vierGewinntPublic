#include "glchessboard.h"
#include "shaderdebugger.h"
#include "gldisc.h"


//#define DEBUG_CHESSBOARD

GLChessboard::GLChessboard(const QVector3D & center, GLfloat squareSize)
    :GLBody("Chessboard")
{
    m_center = center;
    m_normal = v_Y;
    m_squareSize = squareSize;
    m_radius = m_squareSize * 8.0 * 1.142;
    setDrawingMode(GL_TRIANGLES);
}
/**
  * Returns 3D position of field center. Field coordinates are from 0 to 7
  */
QVector3D GLChessboard::fieldToPosition(QPoint field)
{
//    QMatrix4x4 m;
//    m.rotate(90.0, QVector3D::crossProduct( m_normal, v_X));
    QVector3D result;
    QVector3D vx = v_X * m_squareSize;
    QVector3D vz = v_Z * m_squareSize;
    result = (field.x() - 3.5) * vx + (field.y() - 3.5) * vz;
#ifdef DEBUG_CHESSBOARD
    ShaderDebugger::debugVector3D(result, "Field" + QString::number(field.x()) +"," + QString::number(field.y())
                       + " is at position ");
#endif
    return result;
}

void GLChessboard::makeSurface(QVector<GLPoint> *pointContainer, QVector<IndexType> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();

    QVector3D vx = v_X * m_squareSize;
   // vx.debugOutput("ChessBoard::vx: ");
    QVector3D vz = v_Z * m_squareSize;
   // vz.debugOutput("ChessBoard::vz: ");
    for(int row = 0; row <= 8; row ++){
        QVector3D rowStart = m_center + (row - 4) * vz - 4  * vx;
        for (int column = 0; column <= 8; column ++)
        {
          QVector3D vertex = rowStart + column * vx;
          m_points->append(GLPoint(vertex, m_normal));
          if((row < 8) && (column < 8) && (row + column) % 2 == 0)
          {
              m_indices->append(m_firstPoint + row * 9 + column);
              m_indices->append(m_firstPoint + (row + 1) * 9 + column);
              m_indices->append(m_firstPoint + row * 9 + column + 1);
              m_indices->append(m_firstPoint + row * 9 + column + 1);
              m_indices->append(m_firstPoint + (row + 1) * 9 + column);
              m_indices->append(m_firstPoint + (row + 1) * 9 + column + 1);
          }
        }
    }
    m_nextPoint = m_points->size();
    m_nextIndex = m_indices->size();

    /*
    QString s;
    for(int i = m_firstIndex; i < m_nextIndex; i++)
    {
        s += QString::number(indices.at(i)) + " ";
    }
    qDebug("indices: %s", qPrintable(s));
     */
}

/**
  * Raise disc so that it jumps over field.
  */
void GLChessboard::raiseDisc(GLDisc * disc, QPoint field, bool jumpOverKing)
{
    GLfloat distance = (fieldToPosition(field) - QVector3D(disc->getCenter().x(), 0.0, disc->getCenter().z())).length();
    GLfloat radius = 1.41 * m_squareSize;
    GLfloat raiseHeight = 3.0 * disc->getHeight() * (1.0 - distance * distance / radius / radius);
    if(jumpOverKing)
        raiseHeight *= 2.0;
    QVector3D oldCenter = disc->getCenter();
    GLfloat oldHeight = QVector3D::dotProduct(oldCenter, m_normal);
    if(raiseHeight < 0.0)
        raiseHeight = 0.0; //do not dive
    QVector3D vRaise = m_normal * (raiseHeight - oldHeight);
    disc->setCenter(oldCenter + vRaise);
}

/**
  * Returns true, if position is on board.
  */
bool GLChessboard::isOnBoard(const QVector3D & position)
{
    return
            position.x() < m_center.x() + 4.0 * m_squareSize
        &&  position.x() > m_center.x() - 4.0 * m_squareSize
        &&  position.z() < m_center.z() + 4.0 * m_squareSize
        &&  position.z() > m_center.z() - 4.0 * m_squareSize;
}
