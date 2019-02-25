#ifndef GLDISC_H
#define GLDISC_H

#include "glbody.h"
#include "board.h"
class GLDisc : public GLBody
{
public:
    GLDisc(const QString &name, int steps, const QPoint & fieldCoord, float m_radius = 1.0, const GLColorRgba & m_color = GLColorRgba::clBlue, const QString m_textureFile = "",
           float height = 0.5, IndexType slices = 36);
    /**
    *
    * @param pointContainer The container for the geometry data. If NULL, a new one is created.
    * @param indexContainer The container for the index data. If NULL, a new one is created.
    * Created containers will be deleted by destructor.
    */
    void makeSurface(QVector<GLPoint> * pointContainer = nullptr, QVector<GLushort> *indexContainer = nullptr)Q_DECL_OVERRIDE;

    void draw(GLESRenderer *renderer, bool useBuffers)Q_DECL_OVERRIDE;


    float getHeight(){ return m_height;}

    QPoint getFieldCoord() const;
    void setFieldCoord(const QPoint &FieldCoord);

private:
    float m_height;
    IndexType m_slices;
    QPoint m_FieldCoord;
    bool m_isFirst;
    int m_stepsToPosition;
};

#endif // GLDISC_H
