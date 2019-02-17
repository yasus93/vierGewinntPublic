#ifndef GLMOUSERAY_H
#define GLMOUSERAY_H

#include "glbody.h"

class GLMouseRay : public GLBody
{
public:
    GLMouseRay(const QString & name);

    /**
     * @brief setMousePosition Sets up the line for new mouse position
     * @param pos Mouse position as delivered by QMouseEvent (0,0) = left,top
     * @param renderer The renderer with the mvp matrix set as used for drawing the scene.
     */
    void setMousePosition(QPoint pos, GLESRenderer * renderer);

    /**
     * @brief makeSurface Sets the endpoints for the line
     * @param pointContainer
     * @param indexContainer
     */
    void makeSurface(QVector<GLPoint> * pointContainer, QVector<GLushort> *indexContainer) Q_DECL_OVERRIDE;

    /** Draws the surface and calls makeSurface if required.
     * Needs an active (made current) GL-Context.
     * Calls GLBody::draw twice. First call draws a line, second call draws two endpoints.
     */
     virtual void draw(GLESRenderer * renderer, bool useBuffers = false)Q_DECL_OVERRIDE;

     virtual bool isPositionValid() {return m_positionIsValid;}

     virtual void invalidatePosition(){m_positionIsValid = false;}
 private:
    QVector3D m_farPoint;
    QVector3D m_nearPoint;
    bool m_positionIsValid = false;
};

#endif // GLMOUSERAY_H
