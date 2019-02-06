#include "glcube.h"
#include <QVector3D>

GLCube::GLCube(const QString& name, const QVector3D &lbb, const QVector3D &rtf, const QString textureFile) : GLBody (name)
{
    m_lbb = lbb;
    m_rtf = rtf;
   //m_texture = textureFile;
    //m_textureFilenames.append(textureFile);
    //m_showNormals = true;
    //GLBody::setDrawingMode(GL_TRIANGLE_STRIP);
    GLBody::setDrawingMode(GL_TRIANGLES);
    if(!textureFile.isEmpty())
    {
      m_textureFilenames.append(textureFile); //DO NOT call setTextureFile here! It needs a current context!
    }

}

GLCube::~GLCube()
{

}
/**
      Corner vertices of the cube
      ltb_____________rtb
        /            /|
       /            / |
   ltf/____________/rtf
      |   |        |  |
      |   |        |  |
      |lbb|________|__|rbb
      |  /         |  /
      | /          | /
   lbf|/___________|/rbf
*/
void GLCube::makeSurface(QVector<GLPoint> *pointContainer, QVector<IndexType> *indexContainer)
{
    GLBody::makeSurface(pointContainer, indexContainer);

    QVector3D *ltb = new QVector3D(m_lbb.x(), m_rtf.y(), m_lbb.z());
    QVector3D *rbb = new QVector3D(m_rtf.x(), m_lbb.y(), m_lbb.z());
    QVector3D *rtb = new QVector3D(m_rtf.x(), m_rtf.y(), m_lbb.z());
    QVector3D *ltf = new QVector3D(m_lbb.x(), m_rtf.y(), m_rtf.z());
    QVector3D *lbf = new QVector3D(m_lbb.x(), m_lbb.y(), m_rtf.z());
    QVector3D *rbf = new QVector3D(m_rtf.x(), m_lbb.y(), m_rtf.z());


    QVector3D *textur = new QVector3D(0.0, 0.0, 0.0);


    GLBody::makeSurface(pointContainer, indexContainer);

        m_firstPoint = m_points->size();
        m_firstIndex = m_indices->size();

        //Hinten
        QVector3D nh = QVector3D(0, 0, -1);
        m_indices->append(m_points->size());
        m_points->append(GLPoint(m_lbb, nh, QVector3D(0.625, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltb, nh, QVector3D(0.625, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbb, nh, QVector3D(0.75, 0.0, 0.0), GLColorRgba::clGray));

         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbb, nh, QVector3D(0.75, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltb, nh, QVector3D(0.625, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rtb, nh, QVector3D(0.75, 1.0, 0.0), GLColorRgba::clGray));

        //Oben
        QVector3D no = QVector3D(0, 1, 0);
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltf, no, QVector3D(0.5, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltb, no, QVector3D(0.5, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(m_rtf, no, QVector3D(0.625, 0.0, 0.0), GLColorRgba::clGray));

         m_indices->append(m_points->size());
        m_points->append(GLPoint(m_rtf, no, QVector3D(0.625, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltb, no, QVector3D(0.5, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rtb, no, QVector3D(0.625, 1.0, 0.0), GLColorRgba::clGray));

        //Vorne
        QVector3D nv = QVector3D(0, 0, 1);
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*lbf, nv, QVector3D(0.25, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltf, nv, QVector3D(0.25, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbf, nv, QVector3D(0.375, 0.0, 0.0), GLColorRgba::clGray));

         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbf, nv, QVector3D(0.375, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltf, nv, QVector3D(0.25, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(m_rtf, nv, QVector3D(0.375, 1.0, 0.0), GLColorRgba::clGray));

        //Unten
        QVector3D nu = QVector3D(0, -1, 0);
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*lbf, nu, QVector3D(0.0, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(m_lbb, nu, QVector3D(0.0, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbf, nu, QVector3D(0.125, 0.0, 0.0), GLColorRgba::clGray));

         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbf, nu, QVector3D(0.125, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(m_lbb, nu, QVector3D(0.0, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbb, nu, QVector3D(0.125, 1.0, 0.0), GLColorRgba::clGray));

        //Links
        QVector3D nl = QVector3D(-1, 0, 0);
         m_indices->append(m_points->size());
        m_points->append(GLPoint(m_lbb, nl, QVector3D(0.375, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltb, nl, QVector3D(0.375, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*lbf, nl, QVector3D(0.5, 0.0, 0.0), GLColorRgba::clGray));

         m_indices->append(m_points->size());
        m_points->append(GLPoint(*lbf, nl, QVector3D(0.5, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltb, nl, QVector3D(0.375, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*ltf, nl, QVector3D(0.5, 1.0, 0.0), GLColorRgba::clGray));

        //Rechts
        QVector3D nr = QVector3D(1, 0, 0);
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbb, nr, QVector3D(0.25, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rtb, nr, QVector3D(0.25, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbf, nr, QVector3D(0.125, 0.0, 0.0), GLColorRgba::clGray));

         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rbf, nr, QVector3D(0.125, 0.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(*rtb, nr, QVector3D(0.25, 1.0, 0.0), GLColorRgba::clGray));
         m_indices->append(m_points->size());
        m_points->append(GLPoint(m_rtf, nr, QVector3D(0.125, 1.0, 0.0), GLColorRgba::clGray));

        m_nextIndex = m_indices->size();
        m_nextPoint =  m_points->size();


    /*
    if(onlySetOnce == true)
    {
        //m_firstNormalIndex = m_points.size();
        m_firstCubePoint = m_points->size();
        onlySetOnce = false;
    }
    */
//    m_firstIndex = m_indices->size();

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*lbf, -v_Z, QVector3D(0.0, 1.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(m_lbb, -v_Z, QVector3D(0.0, 0.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*rbf, -v_Z, QVector3D(0.125, 1.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*rbb, -v_Z, QVector3D(0.125, 0.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*rtb, -v_Z, QVector3D(0.25, 0.0, 0.0), m_color));


//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*rbf, -v_Z, QVector3D(0.25, 1.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(m_rtf, -v_Z, QVector3D(0.375, 0.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*lbf, -v_Z, QVector3D(0.375, 1.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*ltf, -v_Z, QVector3D(0.5, 0.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(m_lbb, -v_Z, QVector3D(0.5, 1.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*ltb, -v_Z, QVector3D(0.625, 0.0, 0.0), m_color));


//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*rbb, -v_Z, QVector3D(0.625, 1.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*rtb, -v_Z, QVector3D(0.75, 0.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(m_rtf, -v_Z, QVector3D(0.75, 1.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*ltb, -v_Z, QVector3D(0.5, 0.0, 0.0), m_color));

//    m_indices->append(m_points->size());
//    m_points->append(GLPoint(*ltf, -v_Z, QVector3D(0.5, 1.0, 0.0), m_color));



//    m_nextIndex = m_indices->size()-m_firstIndex;




//    m_firstPoint = m_points->size();

    /*Setup sides of Cube */
/*
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(m_lbb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rtb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices->append(static_cast<unsigned short>(m_points->size()));

    m_points->append(GLPoint(m_lbb, -v_X, *textur, GLColorRgba::clCyan));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltb, -v_X, *textur, GLColorRgba::clCyan));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*lbf, -v_X, *textur, GLColorRgba::clCyan));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*lbf, -v_X, *textur, GLColorRgba::clCyan));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltf, -v_X, *textur, GLColorRgba::clCyan));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltb, -v_X, *textur, GLColorRgba::clCyan));
    m_indices->append(static_cast<unsigned short>(m_points->size()));

    m_points->append(GLPoint(*ltb, v_Y, *textur, GLColorRgba::clGreen));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltf, v_Y, *textur, GLColorRgba::clGreen));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rtb, v_Y, *textur, GLColorRgba::clGreen));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rtb, v_Y, *textur, GLColorRgba::clGreen));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(m_rtf, v_Y, *textur, GLColorRgba::clGreen));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltf, v_Y, *textur, GLColorRgba::clGreen));
    m_indices->append(static_cast<unsigned short>(m_points->size()));

    m_points->append(GLPoint(m_lbb, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*lbf, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbb, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbb, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbf, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*lbf, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices->append(static_cast<unsigned short>(m_points->size()));

    m_points->append(GLPoint(*rtb, v_X, *textur, GLColorRgba::clRed));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbb, v_X, *textur, GLColorRgba::clRed));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(m_rtf, v_X, *textur, GLColorRgba::clRed));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(m_rtf, v_X, *textur, GLColorRgba::clRed));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbf, v_X, *textur, GLColorRgba::clRed));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbb, v_X, *textur, GLColorRgba::clRed));
    m_indices->append(static_cast<unsigned short>(m_points->size()));

    m_points->append(GLPoint(*lbf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*rbf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(m_rtf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices->append(static_cast<unsigned short>(m_points->size()));
    m_points->append(GLPoint(*ltf, v_Z, *textur, GLColorRgba::clYellow));
*/
 //   m_nextPoint = m_points->size();
    //m_numberOfNormalVertices = m_points.size() - m_firstNormalIndex;
    //m_lastCubePoint = m_points->size()-1;





}

