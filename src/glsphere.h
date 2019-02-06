#ifndef GLSPHERE_H
#define GLSPHERE_H

#include "glbody.h"

class GLSphere : public GLBody
{
private:
    double m_radius;
    int m_stacks;
    int m_slices;

public:
    GLSphere(const QString& name);
    GLSphere(double radius, int stacks, int slices, const QString textureFile);
    ~GLSphere()override;

    void makeSurface(QVector<GLPoint> * pointContainer, QVector<IndexType> *indexContainer) override;

};

#endif // GLSPHERE_H
