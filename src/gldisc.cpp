#include "gldisc.h"

#include <math.h>
#include "myglitem.h"

GLDisc::GLDisc(const QPoint &fieldCoord, float discRadius, const GLColorRgba &color, const QString textureFile, double height, int slices)
    :GLBody("Disc", discRadius, color, textureFile)
{
    m_fieldCoord = fieldCoord;
    m_discRadius = discRadius;
    m_height = height;
    m_slices = slices;
    m_drawingMode = GL_TRIANGLE_STRIP;
    m_isKing = false;
}

void GLDisc::makeSurface(QVector<GLPoint> *pointContainer, QVector<IndexType> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);
    QVector3D southPole = v_Zero;
    double height = m_height;
    if(m_isKing)
        height *= 2.0;
    QVector3D northPole = v_Y * height;
    QVector3D vertex;// = v_Z * m_discRadius;
    QVector3D normal;
    QVector3D texCoord;
    QMatrix4x4 longitudeMatrix;
    int iSouthPole = 0; //indices for the poles
    int iNorthPole = 0;

    //start with south pole
    m_firstPoint = m_points->size();
    m_firstIndex = m_indices->size();
    iSouthPole = m_firstPoint;
    m_points->append(GLPoint(southPole + m_center,      //vertex
                            -v_Y,            //normal
                           QVector3D(0.125, 0.5, 0.0),//texCoord
                           m_color));

    int slice;
    QVector3D texCenter(0.125f,0.5f,0.0f);
    for(slice = 0; slice <= m_slices; slice ++)
    {
        vertex = v_Z * m_discRadius;
        longitudeMatrix.setToIdentity();//always start from scratch
        if(slice != m_slices) //do not rotate by 360 deg for last points, use 0 deg to match first points
           longitudeMatrix.rotate(slice * 360.0 / m_slices, v_Y);
        //bottom disc 1
        vertex = vertex * longitudeMatrix;
        normal = -v_Y;
        texCoord = texCenter + QVector3D(0.125f * vertex.x() / m_discRadius, -0.5 * vertex.z() / m_discRadius, 0.0);
        m_points->append(GLPoint(vertex + m_center, normal, texCoord, m_color));
        //lower cylinder 2
        normal = vertex;

        //leave tex coord as it is
        m_points->append(GLPoint(vertex + m_center, normal, texCoord, m_color));
       //upper cylinder 3
        vertex += northPole;
        m_points->append(GLPoint(vertex + m_center, normal, texCoord, m_color));
        //top disc 4
        normal = v_Y;
        texCenter= QVector3D(0.875f,0.5f,0.0f);
        texCoord = texCenter + QVector3D(0.125f * vertex.x() / m_discRadius, 0.5 * vertex.z() / m_discRadius, 0.0);
        m_points->append(GLPoint(vertex + m_center, normal, texCoord, m_color));
    }
    //end with north pole
    iNorthPole = m_points->size();
    m_points->append(GLPoint(northPole + m_center,      //vertex
                            v_Y,               //normal
                           QVector3D(0.875, 0.5, 0.0),//texCoord
                           m_color));
    m_nextPoint = m_points->size();

    for(slice = 0; slice < m_slices; slice += 2)
    {
        int leftSlice = iSouthPole + 4 * slice;
        int rightSlice = iSouthPole + 4 * (slice + 1);
        //we go upwards from south pole to north pole first
        m_indices->append(iSouthPole);
        m_indices->append(leftSlice + 1); //left bottom disc
        m_indices->append(rightSlice + 1); //right bottom disc
        m_indices->append(rightSlice + 2); //right bottom cylinder
        m_indices->append(leftSlice + 2); //left bottom cylinder
        m_indices->append(rightSlice + 3); //right top cylinder
        m_indices->append(leftSlice + 3 ); //left top cylinder
        m_indices->append(leftSlice + 4); //left top disc
        m_indices->append(rightSlice + 4); //right top disc
        m_indices->append(iNorthPole);
        //we go downwards, back to southpole
        leftSlice += 4;
        rightSlice += 4;
        m_indices->append(rightSlice + 4); //right top disc
        m_indices->append(leftSlice + 4); //left top disc
        m_indices->append(rightSlice + 3); //right top cylinder
        m_indices->append(leftSlice + 3); //left top cylinder
        m_indices->append(rightSlice + 2); //right bottom cylinder
        m_indices->append(leftSlice + 2); //left bottom cylinder
        m_indices->append(leftSlice + 1); //left bottom disc
        m_indices->append(rightSlice + 1); //right bottom disc
        //southpole will be added in next slice
    }

    m_indices->append(iSouthPole); //finally add south pole

    m_nextIndex = m_indices->size();

    rotateModelPoints(v_XYZ, v_Z, 90.0f);
    //move(v_Z);
}


QPoint GLDisc::getFieldCoord() const
{
    return m_fieldCoord;
}

void GLDisc::setFieldCoord(const QPoint &FieldCoord)
{
    m_fieldCoord = FieldCoord;
}

void GLDisc::becomeKing()
{
    if(m_isKing)
            return;
   // m_height = 2* m_height;
    m_isKing = true;

    invalidateSurface();

}

double GLDisc::getDiscRadius() const
{
    return m_discRadius;
}

double GLDisc::getHeight() const
{
    return m_height;
}

bool GLDisc::isColliding(const GLDisc *other) const
{
    if(this == other)
        return false;

    if((getCenter() - other->getCenter()).length() > getDiscRadius() + other->getDiscRadius())
        return false;
    else
    {
        double otherHeight = other->m_height;
        if(other->m_isKing)
            otherHeight *= 2.0;
        double ourHeight = m_height;
        if(m_isKing)
            ourHeight *= 2.0;
        if(getCenter().y() < other->getCenter().y())
            return other->getCenter().y() - getCenter().y() <= ourHeight;
        else return getCenter().y() - other->getCenter().y() <= otherHeight;
    }
}

bool GLDisc::isHit(QVector3D p1, QVector3D p2)
{
    bool rueckgabe = false;
    if(GLBody::isHit(p1, p2))
    {
        qDebug() << "Treffer";
        QVector3D inter = QVector3D(0.0,0.0,0.0);

        mouseIntersection(&inter, QVector3D(0.0,0.0,1.0), 0.0, p1, p2);
        if(inter.distanceToPoint(QVector3D(0.0,0.0,0.0)) <= m_radius)
        {
            rueckgabe =  true;
        }
        else
        {
            mouseIntersection(&inter, QVector3D(0.0,0.0, 1.0), m_height, p1, p2);
            if(inter.distanceToPoint(QVector3D(0.0,0.0,0.0)) <= m_radius)
            {
                rueckgabe = true;
            }
            else
            {
                //mouseIntersection(&inter, QVector3D(0.0,0.0, 1.0), m_height, p1, p2);
                float x1 = p1.x();
                float y1 = p1.y();
                float x2 = p2.x();
                float y2 = p2.y();
                float untermbruch = ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) );
                float p = (2*x1*(x2-x1) + 2*y1*(y2-y1)) / untermbruch;
                float q = (x1*x1 + y2*y2 - m_radius*m_radius) / untermbruch;
                float unterwurzel = (p/2)*(p/2) -q;


                if (unterwurzel < 0)
                {
                    rueckgabe = false;
                }
                else
                {
                    float loesung1 = -p/2 + sqrt(unterwurzel);
                    float loesung2 = -p/2 - sqrt(unterwurzel);
                    if (loesung1 < m_radius || loesung2 < m_radius)
                    {
                        rueckgabe = true;
                    }
                }
            }
        }

    }

    return rueckgabe;

}

bool GLDisc::mouseIntersection(QVector3D * intersection, QVector3D normal, float d, QVector3D p1, QVector3D p2)
{
    float m0, m15;
    QVector3D v = p1 - p2; //vector from near to far clipping plane
    m15 = d + QVector3D::dotProduct(normal, p1);
    m0 = QVector3D::dotProduct( normal, v);
    if(fabs(m0) < fabs(m15)) //we have no intersection in frustum (lambda will be > 1.0)
    {
       return false;
    }
    float lambda = -m15  / m0;
    * intersection = p1 + lambda * v;
    return true;
}
