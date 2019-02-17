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

    QList<GLDisc *> redDiscs;
    QList<GLDisc *> yellowDiscs;
    GLBody *m_blender;
    Board *field;

    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int counter7 = 0;

    int totalDiscs = 0;

    int currentTheme = 2;

    GLColorRgba color;


public:
    MyGlItem();

    virtual void setupGeometry() override;

    void paintUnderQmlScene() override;
    void paintOnTopOfQmlScene() override;



public slots:
    void insertDisc(int buttonNumber);
    void doMouseClick(int x, int y);
    void newGame();
    void changeTheme(int theme);

protected:


};

#endif // MYGLITEM_H
