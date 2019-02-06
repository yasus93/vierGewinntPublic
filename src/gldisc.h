#ifndef GLDISC_H
#define GLDISC_H

#include "glbody.h"

class GLDisc : public GLBody
{

private:
   QPoint m_fieldCoord;
   double m_height;
   double m_discRadius;
   int m_slices;
   bool m_isKing;

public:
    GLDisc(const QPoint& fieldCoord, float m_radius = 1.0, const GLColorRgba& m_color = GLColorRgba::clBlue,
               const QString m_textureFile = "", double height = 0.5, int slices = 36);

    void makeSurface(QVector<GLPoint>* pointContainer = NULL, QVector<IndexType>* indexContainer = NULL);

    bool isColliding(const GLDisc* other)const;

    void setFieldCoord(const QPoint& FieldCoord);

    QPoint getFieldCoord() const;
    double getHeight()const;
       void becomeKing();
    double getDiscRadius()const;
    bool isHit(QVector3D p1, QVector3D p2);

    bool mouseIntersection(QVector3D * intersection, QVector3D normal, float d, QVector3D p1, QVector3D p2);

};

#endif // GLDISC_H
