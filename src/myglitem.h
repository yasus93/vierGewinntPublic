#ifndef MYGLITEM_H
#define MYGLITEM_H

#include "glitem.h"
#include "gldisc.h"
#include <QOpenGLBuffer>
#include "glmouseray.h"
#include "board.h"

class MyGlItem : public GLItem
{
    Q_OBJECT

private:

    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;

    QList<GLDisc *> whiteDiscs;
    QList<GLDisc *> blackDiscs;
    GLBody *m_blender;
    Board *field;

    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int counter7 = 0;


public:
    MyGlItem();

    virtual void setupGeometry() override;

    void paintUnderQmlScene() override;
    void paintOnTopOfQmlScene() override;



public slots:
    void insertDisc(int x, int y);
    void doMouseClick(int x, int y);

protected:


};

#endif // MYGLITEM_H
