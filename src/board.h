#ifndef BOARD_H
#define BOARD_H

#include "glbody.h"
#include <QPoint>

class GLDisc;
/**
  * \brief A chess board with 7X6 fields.
  *
  * This Board is created for the positioning of discs.
  * It should not be drawn in final use.
  * The fieldToPosition function returns the 3D-coordinates of the field in model space.
  * Three points are used to define starting position. Deltas are used to norm vertices.
  */
class Board : public GLBody
{
public:
    Board();
     /**
     * @brief fieldToPosition
     * @param field
     * @return 3D position of field center. Field coordinates are from 0 to 7
     */
    QVector3D fieldToPosition(QPoint field);

    /**
     * @brief makeSurface
     * @param pointContainer The container for the geometry data. If NULL, a new one is created.
     * @param indexContainer The container for the index data. If NULL, a new one is created.
     *
     * Created containers will be deleted by destructor.
     */
    void makeSurface(QVector<GLPoint> * pointContainer = nullptr, QVector<IndexType> * indexContainer = nullptr);

private:
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
