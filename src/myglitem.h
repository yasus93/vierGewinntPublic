#ifndef MYGLITEM_H
#define MYGLITEM_H

#include "glitem.h"
#include "gldisc.h"
#include <QOpenGLBuffer>
#include "glmouseray.h"

class MyGlItem : public GLItem
{
    Q_OBJECT

private:

    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;
    bool onlySetOnce;

    GLDisc *m_disc;
    QList<GLDisc *> whiteDiscs;
    QList<GLDisc *> blackDiscs;
    GLMouseRay *m_mouseRay;
    GLBody *m_blender;




public:
    MyGlItem();
    virtual void setupGeometry() override;

    void paintUnderQmlScene() override;
    void paintOnTopOfQmlScene() override;



public slots:

protected:


};

#endif // MYGLITEM_H
