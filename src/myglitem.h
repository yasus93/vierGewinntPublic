#ifndef MYGLITEM_H
#define MYGLITEM_H

#include "glitem.h"
#include "glcube.h"
#include "glsphere.h"
#include "glchessboard.h"
#include "gldisc.h"
#include <QOpenGLBuffer>
#include "glmouseray.h"

class MyGlItem : public GLItem
{
    Q_OBJECT

private:
    GLint m_firstTrianglePoint;
    GLint m_lastTrianglePoint;
    int m_firstCubePoint;
    int m_lastCubePoint;
    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;
    bool onlySetOnce;
    int m_firstNormalIndex;
    int m_numberOfNormalVertices;
    GLCube *m_cube;
    GLSphere *m_sphere;
    GLDisc *m_disc;
    GLChessboard *m_chessboard;
    QList<GLDisc *> whiteDiscs;
    QList<GLDisc *> blackDiscs;
    GLMouseRay *m_mouseRay;




public:
    MyGlItem();
    virtual void setupGeometry() override;

    void createTriangles();
    void drawTriangles();

    void createCube(const QVector3D &lbb, const QVector3D &rtf);
    void drawCube();

    void createF(double height);
    void drawF(double height);

    void paintUnderQmlScene() override;
    void paintOnTopOfQmlScene() override;

    void createVisibleNormals();
    void drawNormals();



    void createGame();

public slots:
    void onMouseClicked(int x, int y);
    void toggleUp();

protected:


};

#endif // MYGLITEM_H
