
#include "glsphere.h"
#include "glbody.h"
#include <math.h>

GLSphere::GLSphere(const QString &name):GLBody(name)
{

}

GLSphere::GLSphere(double radius, int stacks, int slices, const QString textureFile):GLBody ("Default")
{
    m_radius = radius;
    m_stacks = stacks;
    m_slices = slices;
    GLBody::setDrawingMode(GL_TRIANGLE_STRIP);
    m_showNormals= true;
    if(!textureFile.isEmpty())
    {
      m_textureFilenames.append(textureFile); //DO NOT call setTextureFile here! It needs a current context!
    }
}

GLSphere::~GLSphere()
{

}

void GLSphere::makeSurface(QVector<GLPoint> *pointContainer, QVector<IndexType> *indexContainer)
{

    GLBody::makeSurface(pointContainer, indexContainer);

    GLBody::makeSurface(pointContainer, indexContainer);
        m_firstPoint = static_cast<GLushort>(m_points->size());
        m_firstIndex = static_cast<GLushort>(m_indices->size());
        m_points->append(GLPoint(-v_Y * m_radius, -v_Y, QVector3D(0.5,0.0,0.0), m_color)); //south pole
        QMatrix4x4 zRotator;
        QMatrix4x4 yRotator;
        for(int slice = 0; slice < m_slices; slice++){
            yRotator.setToIdentity();
            yRotator.rotate(slice * 360.0 / (double)m_slices, v_Y);

            for(int stack = 0; stack <= m_stacks; stack ++){
                QVector3D texCoord = QVector3D(slice * 1.0 / m_slices, stack * 1.0 / m_stacks, 0.0);
                QVector3D vertex = -v_Y;
                zRotator.setToIdentity();
                double zAngle = stack * 180.0 / (double) m_stacks;
                zRotator.rotate(zAngle, v_Z);
                vertex= yRotator * zRotator * vertex;
                m_points->append(GLPoint(vertex * m_radius, vertex,texCoord, m_color));
            }
        }

        //add last column as a copy of the first column.
        //however change textCoords to end of texture
        for (int stack = 0; stack < m_stacks; stack++){
            int i = m_firstPoint + stack + 1;
            QVector3D texCoord = QVector3D(1.0, stack * 1.0 / m_stacks, 0.0);
            GLPoint point = GLPoint(m_points->at(i).vertex(), m_points->at(i).normal(), texCoord, m_color);
            m_points->append(point);
        }


        //set the indices for a single triangle strip
        for(int slice = 0; slice < m_slices; slice += 2){ //proceed two slices!!
            //bottom triangle
            int stack = 0;
            for(stack = 0; stack <= m_stacks; stack++){ //from south to north
                m_indices->append(static_cast<GLushort>(slice * (m_stacks + 1) + stack));
                m_indices->append(static_cast<GLushort>((slice + 1) * (m_stacks + 1) + stack));
            }
            m_indices->append(static_cast<GLushort>((slice + 1) * (m_stacks + 1) + stack));
            for(int stack = m_stacks; stack >= 0; stack--){//back again from north to south
                m_indices->append(static_cast<GLushort>((slice + 2) * (m_stacks + 1) + stack));
                m_indices->append(static_cast<GLushort>((slice + 1) * (m_stacks + 1) + stack));
            }
            m_indices->append(static_cast<GLushort>((slice + 2) * (m_stacks + 1) + stack));
        }
        m_nextPoint = static_cast<GLushort>(m_points->size());
        m_nextIndex = static_cast<GLushort>(m_indices->size());
}

