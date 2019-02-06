#ifndef GLCUBE_H
#define GLCUBE_H

#include "glbody.h"
#include <QVector3D>



class GLCube : public GLBody
{
private:
     QVector3D m_lbb;
     QVector3D m_rtf;
     QString m_texture;


public:
    GLCube(const QString& name, const QVector3D &lbb, const QVector3D &rtf, const QString textureFile);
    ~GLCube()override;

    void makeSurface(QVector<GLPoint> * pointContainer, QVector<IndexType> *indexContainer) override;
};

#endif // GLCUBE_H
