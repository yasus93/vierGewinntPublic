#ifndef BOARD_H
#define BOARD_H

#include "glbody.h"
#include <QPoint>

class GLDisc;
/**
  * A chess board with 8X8 fields in the x-z plane.
  * Only the white fields are drawn, black fields are transparent.
  * The raiseDisc function makes a disc "jump" over the respective field.
  * The fieldToPosition function returns the 3D-coordinates of the field in model space.
  * isOnBoard returns true, when position is "on" the board.
  */
class Board : public GLBody
{
public:
    Board();
    /**
      * Returns 3D position of field center. Field coordinates are from 0 to 7
      */
    QVector3D fieldToPosition(QPoint field);

    void makeSurface(QVector<GLPoint> * pointContainer = nullptr, QVector<IndexType> * indexContainer = nullptr);

protected:
    /**
      * The normal on the chessboard plane
      */
    QVector3D m_normal;

    QVector3D *b_firstPoint;
    QVector3D *b_secondPoint;
    QVector3D *b_thirdPoint;

    QList<QVector3D> columnPoints;

    float deltaX;
    float deltaY;
    float deltaZ;
};

#endif // BOARD_H
