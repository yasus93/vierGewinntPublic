#ifndef GLDISC_H
#define GLDISC_H

#include "glbody.h"
class GLDisc : public GLBody
{
public:
    GLDisc(const QString &name, const QPoint & fieldCoord, float m_radius = 1.0, const GLColorRgba & m_color = GLColorRgba::clBlue, const QString m_textureFile = "",
           float height = 0.5, IndexType slices = 36);
    /**
    *
    * @param pointContainer The container for the geometry data. If NULL, a new one is created.
    * @param indexContainer The container for the index data. If NULL, a new one is created.
    * Created containers will be deleted by destructor.
    */
    void makeSurface(QVector<GLPoint> * pointContainer = nullptr, QVector<GLushort> *indexContainer = nullptr)Q_DECL_OVERRIDE;

    void draw(GLESRenderer *renderer, bool useBuffers = false)Q_DECL_OVERRIDE;

    float getHeight(){ return m_height;}
    QPoint getFieldCoord() const;
    void setFieldCoord(const QPoint &FieldCoord);
    void becomeKing();
    bool isKing() {return m_isKing;}
    /**
      * Returns true, if discs are colliding
      */
    bool isColliding(const GLDisc * other);

private:
    float m_height;
    IndexType m_slices;
    QPoint m_FieldCoord;
    bool m_isKing;
};

#endif // GLDISC_H
