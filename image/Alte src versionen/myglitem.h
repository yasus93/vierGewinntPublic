#ifndef MYGLITEM_H
#define MYGLITEM_H

#include "glitem.h"

class MyGlItem : public GLItem
{
private:
    int m_firstTrianglePoint;
    int m_lastTrianglePoint;

public:
    MyGlItem();
    virtual void setupGeometry() override;

    void createTriangles();
    void drawTriangles();
   // void paintUnderQmlScene() override;
    void paintOnTopOfQmlScene() override {qDebug()<<"overridden paintOnTop was called"; drawTriangles();}

protected:


};

#endif // MYGLITEM_H
