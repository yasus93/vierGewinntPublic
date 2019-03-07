#include "gldisc.h"
#include <math.h>

GLDisc::GLDisc(const QString & name, int steps, const QPoint &fieldCoord, float radius, const GLColorRgba &color, const QString textureFile, float height, IndexType slices)
    :GLBody(name, radius, color, textureFile)
{
    m_FieldCoord = fieldCoord;
    m_height = height;
    m_slices = slices;
    m_drawingMode = GL_TRIANGLE_STRIP;
    m_isFirst = true;
    m_stepsToPosition = steps;
}

void GLDisc::makeSurface(QVector<GLPoint> *pointContainer, QVector<GLushort> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);

    QVector3D southPole = v_Zero; //unit vector, must be scaled by radius later
    QVector3D northPole = v_Y * m_height;
    QVector3D vertex = v_Z * m_radius;
    QVector3D normal;
    QVector3D texCoord;
    QMatrix4x4 longitudeMatrix;
    IndexType iSouthPole = 0; //indices for the poles
    IndexType iNorthPole = 0;

    //start with south pole
    m_firstPoint =  static_cast<IndexType>(m_points->size());
    m_firstIndex = static_cast<IndexType>(m_indices->size());
    iSouthPole = m_firstPoint;
    m_points->append(GLPoint(southPole + m_center,      //vertex
                            -v_Y,            //normal
                           QVector3D(0.5, 0.5, 0.0),//texCoord
                           m_color));

    IndexType slice;
    QVector3D texCenter(0.5,0.5,0.0);
    for(slice = 0; slice <= m_slices; slice ++)
    {
        vertex = v_Z * m_radius;
        longitudeMatrix.setToIdentity();//always start from scratch
        if(slice != m_slices) //do not rotate by 360 deg for last points, use 0 deg to match first points
           longitudeMatrix.rotate(slice * 360.0f / m_slices, -v_Y);
        //bottom disc 1
        vertex = vertex * longitudeMatrix;
        normal = -v_Y;
        texCoord = texCenter + QVector3D(0.5f * vertex.x() / m_radius, -0.5f * vertex.z() / m_radius, 0.0);
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
        m_points->append(GLPoint(vertex + m_center, normal, texCoord, m_color));
    }
    //end with north pole
    iNorthPole = static_cast<IndexType>(m_points->size());
    m_points->append(GLPoint(northPole * m_radius + m_center,      //vertex
                            v_Y,               //normal
                           QVector3D(0.5, 0.5, 0.0),//texCoord
                           m_color));
    m_nextPoint = static_cast<IndexType>(m_points->size());

    for(slice = 0; slice < m_slices; slice += 2)
    {
        IndexType leftSlice = iSouthPole + 4 * slice;
        IndexType rightSlice = iSouthPole + 4 * (slice + 1);
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

    m_nextIndex = static_cast<IndexType>(m_indices->size());

    rotateModelPoints(v_XYZ, v_Z, 90.0f);

    if(m_showNormals)
        createNormals();
}

void GLDisc::draw(GLESRenderer *renderer, bool useBuffers)
{
    if(m_stepsToPosition > 0 && !m_isFirst)
    {
        this->move(QVector3D(0.0f, -0.4f, 0.0f));
        m_stepsToPosition -= 2;
    }
    m_isFirst = false;

    GLBody::draw(renderer, useBuffers);
}


QPoint GLDisc::getFieldCoord() const
{
    return m_FieldCoord;
}

void GLDisc::setFieldCoord(const QPoint &FieldCoord)
{
    m_FieldCoord = FieldCoord;
}

