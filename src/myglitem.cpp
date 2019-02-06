#include "myglitem.h"
#include "glitem.h"
#include "glpoint.h"
#include <QVector3D>
#include "glmouseray.h"

MyGlItem::MyGlItem() : GLItem()
{
    m_backgroundColor = GLColorRgba::clBlack;
    m_drawAxes = true;
    m_firstTrianglePoint = 0;
    m_lastTrianglePoint = 0;
    m_activatePaintAfterQml = true;
    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_firstCubePoint = 0;
    m_lastCubePoint = 0;
    onlySetOnce = true;
    //m_eye *= 0.5f;
    //m_eye = 10.0 * v_Y;
    //m_orthoMode =true;
    m_firstNormalIndex = 0;
    m_numberOfNormalVertices = 0;

    m_fovy         = 45.0f;
        m_aspect       =  0.0f;
        m_eye = 8.5 * v_YZ;

        m_orthoMode    = false;
        m_orthoRange   = 1.0;
        m_mouseRay = NULL;
}

void MyGlItem::toggleUp()
{

}

void MyGlItem::createVisibleNormals()
{
    qDebug() << m_firstNormalIndex;
    qDebug() << m_numberOfNormalVertices;
    m_firstNormalIndex = m_points.size();
    for (int i = m_firstCubePoint; i < m_lastCubePoint; i++)
    {
        m_points.append(GLPoint(m_points.at(i).vertex()));
        m_points.append((GLPoint(m_points.at(i).vertex() + m_points.at(i).normal())));
    }
    m_numberOfNormalVertices = m_points.size() - m_firstNormalIndex + 1;
}

void MyGlItem::drawNormals()

{
    renderer()->setLightingEnabled(false); //switchofflighting
    glDrawArrays(GL_LINES, m_firstNormalIndex, m_numberOfNormalVertices);

    renderer()->setLightingEnabled(m_lightingEnabled);
}

void MyGlItem::paintOnTopOfQmlScene()
{
   // qDebug()<<"overridden paintOnTop was called";

    //drawCube();
    //drawTriangles();
    //createF(5.0);
    //drawF(5.0);
    //drawNormals();
    //drawCube();
    //m_cube->draw(m_renderer, false);
    m_sphere->draw(m_renderer, false);
    //m_disc->draw(m_renderer, false);
    //m_mouseRay->draw(m_renderer);

    /*
    m_chessboard->draw(m_renderer, false);
    for (int i = 0; i < whiteDiscs.size(); i++)
        whiteDiscs[i]->draw(m_renderer);
    for (int i = 0; i < blackDiscs.size(); i++)
        blackDiscs[i]->draw(m_renderer);
    if(m_mouseRay!=nullptr)
    {
        m_mouseRay->draw(m_renderer);
    }
    */
}

void MyGlItem::createF(double height)
{

    createCube(v_Zero, QVector3D(1.0, static_cast<float>(height), 1.0));
    createCube(QVector3D(1.0, static_cast<float>(height-1.0), 0.0), QVector3D(static_cast<float>(height*0.5), static_cast<float>(height), 1.0));
    createCube(QVector3D(1.0, static_cast<float>(height-3.0), 0.0), QVector3D(static_cast<float>(height*0.35), static_cast<float>(height-2.0), 1.0));

    qDebug() << m_points.size();
}

void MyGlItem::drawF(double height)
{
    m_renderer->scale(QVector3D(1.0, static_cast<float>(height), 1.0));
    drawCube();
    m_renderer->translate(QVector3D(1.0, 0.0, 0.0));
    m_renderer->scale(QVector3D(2.0, static_cast<float>(0.2), 1.0));
    m_renderer->translate(QVector3D(0.0, 4.0, 0.0));
    drawCube();
    m_renderer->scale(QVector3D(0.5, 1.0, 1.0));
    m_renderer->translate(QVector3D(0.0, -2.0, 0.0));
    drawCube();

    qDebug() << m_points.size();
}

void MyGlItem::drawCube()
{
    if(m_lastCubePoint < m_firstCubePoint) //We have no points for cube
    {
        qDebug() << "GLItem::drawCube(): No data available.";
        return;
    }
    qDebug() << "drawCube was called and checked";

    m_vertexBuffer->bind();
    m_indexBuffer->bind();

    m_renderer->setColorArrayEnabled(true);
    m_renderer->setLightingEnabled(true);


    m_renderer->activateAttributeBuffer(GLESRenderer::VERTEX_LOCATION);
    m_renderer->activateAttributeBuffer(GLESRenderer::COLOR_LOCATION);
    m_renderer->activateAttributeBuffer(GLESRenderer::NORMAL_LOCATION);
    m_renderer->activateAttributeBuffer(GLESRenderer::TEXCOORD_LOCATION);

    qDebug() << "Bis hierhin läuft";

    //glDrawArrays(GL_TRIANGLES, m_firstCubePoint, m_lastCubePoint - m_firstCubePoint + 1); //Triangle Coordinate
    glDrawElements(GL_TRIANGLES, m_lastCubePoint - m_firstCubePoint + 1, GL_UNSIGNED_SHORT, nullptr);

    //restore old settings
    m_renderer->disableAttributeArrays();
    m_vertexBuffer->release();
    m_indexBuffer->release();
    m_renderer->setColorArrayEnabled(m_colorArrayEnabled);
    m_renderer->setLightingEnabled(m_lightingEnabled);

    drawNormals();

}
void MyGlItem::paintUnderQmlScene()
{
    //qDebug()<<"Overridden paintUnder was called";

}

void MyGlItem::createGame()
{
    m_chessboard = new GLChessboard();
    m_chessboard->makeSurface();

    for(int column = 0; column < 8; column ++)
        {
            for(int row = 0; row < 3; row ++)
            {
                if((row + column) % 2 != 0) //black fields only
                {
                    QPoint field = QPoint(column, row);
                    GLDisc * disc = new GLDisc(field, 0.45f, GLColorRgba::clWhite, ":/textures/muehlestein.jpg", 0.25f);
                    //disc->setTextureFile(":/textures/white_disc.jpg");
                    disc->setCenter(m_chessboard->fieldToPosition(disc->getFieldCoord()));
                    whiteDiscs.append (disc);
                    field = QPoint(7 - column, 7 -row);
                    disc = new GLDisc( field, 0.45f, GLColorRgba::clBlack, ":/textures/blackmuehlestein.jpg", 0.25f);
                    //disc->setTextureFile(":/textures/black_disc.jpg");
                    disc->setCenter(m_chessboard->fieldToPosition(disc->getFieldCoord()));
                    blackDiscs.append (disc);
                }
            }
        }


    //m_disc = new GLDisc(QPoint(0, 0), 0.5f, GLColorRgba::clGray, ":/textures/muehlestein.jpg");
    //m_disc->makeSurface();
}

void MyGlItem::onMouseClicked(int x, int y)
{
    qDebug() << x << y;
    m_mouseRay = new GLMouseRay();
    QVector3D *nah = new QVector3D();
    QVector3D *fern = new QVector3D();
    m_renderer->calculateMousePoints(nah , fern, QPoint(x, y));

    m_mouseRay->makeSurface(*nah, *fern);
    qDebug() << *nah << *fern;

    for (int i = 0; i < whiteDiscs.size(); i++)
        if(whiteDiscs[i]->isHit(*nah, *fern))
            qDebug() << "Treffer weiß";
    for (int i = 0; i < blackDiscs.size(); i++)
        if(blackDiscs[i]->isHit(*nah, *fern))
            qDebug() << "Treffer Schwarz";

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
void MyGlItem::createCube(const QVector3D &lbb, const QVector3D &rtf)
{

   // m_cube = new GLCube("Test", lbb, rtf, ":/textures/dice.png");
    //m_cube->makeSurface(nullptr, nullptr);

    m_sphere = new GLSphere(4.0, 20, 20, ":/textures/earthmap1k.jpg");
    m_sphere->makeSurface(nullptr, nullptr);



    /*
    QVector3D *ltb = new QVector3D(lbb.x(), rtf.y(), lbb.z());
    QVector3D *rbb = new QVector3D(rtf.x(), lbb.y(), lbb.z());
    QVector3D *rtb = new QVector3D(rtf.x(), rtf.y(), lbb.z());
    QVector3D *ltf = new QVector3D(lbb.x(), rtf.y(), rtf.z());
    QVector3D *lbf = new QVector3D(lbb.x(), lbb.y(), rtf.z());
    QVector3D *rbf = new QVector3D(rtf.x(), lbb.y(), rtf.z());

    QVector3D *textur = new QVector3D(0.0, 0.0, 0.0);

    if(onlySetOnce == true)
    {
        //m_firstNormalIndex = m_points.size();
        m_firstCubePoint = m_points.size();
        onlySetOnce = false;
    }


    Setup sides of Cube

    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(lbb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rtb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltb, -v_Z, *textur, GLColorRgba::clBlue));
    m_indices.append(static_cast<unsigned short>(m_points.size()));

    m_points.append(GLPoint(lbb, -v_X, *textur, GLColorRgba::clCyan));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltb, -v_X, *textur, GLColorRgba::clCyan));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*lbf, -v_X, *textur, GLColorRgba::clCyan));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*lbf, -v_X, *textur, GLColorRgba::clCyan));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltf, -v_X, *textur, GLColorRgba::clCyan));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltb, -v_X, *textur, GLColorRgba::clCyan));
    m_indices.append(static_cast<unsigned short>(m_points.size()));

    m_points.append(GLPoint(*ltb, v_Y, *textur, GLColorRgba::clGreen));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltf, v_Y, *textur, GLColorRgba::clGreen));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rtb, v_Y, *textur, GLColorRgba::clGreen));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rtb, v_Y, *textur, GLColorRgba::clGreen));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(rtf, v_Y, *textur, GLColorRgba::clGreen));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltf, v_Y, *textur, GLColorRgba::clGreen));
    m_indices.append(static_cast<unsigned short>(m_points.size()));

    m_points.append(GLPoint(lbb, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*lbf, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbb, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbb, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbf, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*lbf, -v_Y, *textur, GLColorRgba::clMagenta));
    m_indices.append(static_cast<unsigned short>(m_points.size()));

    m_points.append(GLPoint(*rtb, v_X, *textur, GLColorRgba::clRed));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbb, v_X, *textur, GLColorRgba::clRed));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(rtf, v_X, *textur, GLColorRgba::clRed));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(rtf, v_X, *textur, GLColorRgba::clRed));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbf, v_X, *textur, GLColorRgba::clRed));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbb, v_X, *textur, GLColorRgba::clRed));
    m_indices.append(static_cast<unsigned short>(m_points.size()));

    m_points.append(GLPoint(*lbf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*rbf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(rtf, v_Z, *textur, GLColorRgba::clYellow));
    m_indices.append(static_cast<unsigned short>(m_points.size()));
    m_points.append(GLPoint(*ltf, v_Z, *textur, GLColorRgba::clYellow));

    m_lastCubePoint = m_points.size()-1;

    */
}

void::MyGlItem::drawTriangles()
{
    if(m_lastTrianglePoint < m_firstTrianglePoint) //We have no axes
    {
        qDebug() << "GLItem::drawTriangles(): No data available.";
        return;
    }
    qDebug() << "drawTriangles was called and checked";

    m_vertexBuffer->bind();
    m_indexBuffer->bind();
    m_renderer->setColorArrayEnabled(true);

    m_renderer->setLightingEnabled(false);
    //int stride = sizeof(GLPoint);
    /*m_renderer->activateAttributeArray(GLESRenderer::VERTEX_LOCATION,
                                       m_points[0].vertexPointer(), stride);
    m_renderer->activateAttributeArray(GLESRenderer::COLOR_LOCATION,
                                       m_points[0].colorPointer(), stride);
    */

    m_renderer->activateAttributeBuffer(GLESRenderer::VERTEX_LOCATION);
    m_renderer->activateAttributeBuffer(GLESRenderer::COLOR_LOCATION);
    qDebug() << "Bis hierhin läuft";
    //glDrawArrays(GL_TRIANGLES, m_firstTrianglePoint, m_lastTrianglePoint - m_firstTrianglePoint + 1); //Triangle Coordinate
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);

    m_renderer->disableAttributeArrays();
    //restore old settings
    m_vertexBuffer->release();
    m_indexBuffer->release();
    m_renderer->setColorArrayEnabled(m_colorArrayEnabled);
    m_renderer->setLightingEnabled(m_lightingEnabled);


}

void MyGlItem::createTriangles()
{
    qDebug() << "create Triangles was called";

    m_firstTrianglePoint = static_cast<GLint>(m_points.size()) ;
    qDebug() << m_firstTrianglePoint;
    GLPoint *first = new GLPoint(QVector3D(0.0, 0.0, 0.0) , QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 0.0, 0.0), GLColorRgba::clRed);
    m_points.append(*first);
    m_indices.append(static_cast<unsigned short>(m_firstTrianglePoint));
    m_points.append(GLPoint(QVector3D(2.0, 0.0, 0.0) , QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 0.0, 0.0), GLColorRgba::clGreen));
    m_points.append(GLPoint(QVector3D(0.0, 2.0, 0.0) , QVector3D(0.0, 0.0, 1.0), QVector3D(0.0, 0.0, 0.0), GLColorRgba::clBlue));
    m_lastTrianglePoint = static_cast<GLint>(m_points.size()-1);
    qDebug() << m_lastTrianglePoint;
    m_indices.append(static_cast<unsigned short>(m_firstTrianglePoint+1));
    m_indices.append(static_cast<unsigned short>(m_lastTrianglePoint));
}

void MyGlItem::setupGeometry()
{
    GLItem::setupGeometry();

    //createGame();
    createCube(QVector3D(0.0, 0.0, 0.0), QVector3D(1.0, 1.0, 1.0));
    //createTriangles();
    //createF(5.0);
    /*
    createVisibleNormals();

    if(!m_vertexBuffer->create())
    {
        qDebug() << "Vertex Buffer create failed";
        exit(1);
    }
    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(m_points.data(), m_points.size() * static_cast<int>(sizeof (GLPoint)));
    m_vertexBuffer->release();

    if(!m_indexBuffer->create())
    {
        qDebug() << "IndexBuffer create failed";
    }
    m_indexBuffer->bind();
    m_indexBuffer->allocate(m_indices.data(), m_indices.size()* static_cast<int>(sizeof(IndexType)));
    m_indexBuffer->release();
*/
}
