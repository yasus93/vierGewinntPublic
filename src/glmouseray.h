#ifndef GLMOUSERAY_H
#define GLMOUSERAY_H

#include "glbody.h"

class GLMouseRay: public GLBody
{
public:
    GLMouseRay();
    void makeSurface(QVector3D nah, QVector3D fern);
};

#endif // GLMOUSERAY_H
