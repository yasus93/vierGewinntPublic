/********************************************************
 * Convenience objects for building OpenGL surfaces.
 *
 *  Created on: 24.04.2012
 *      Author: Walter Roth
 *  Copyright by Walter Roth 2012, Licence: GPL
 *
 *******************************************************/

/** \file
  * \brief Convenience objects for building OpenGL surfaces.
  *
  * Predefined 3D-vectors and colors that are frequently used.
  */

#ifndef GLDEFINES_H
#define GLDEFINES_H

#include <QVector3D>
#include "glcolorrgba.h"

#define IndexType GLushort
//#define USE_QOPENGL_FUNCTIONS

//Predefined vectors

const static QVector3D v_Zero = QVector3D(0.0, 0.0, 0.0);
const static QVector3D v_X = QVector3D(1.0, 0.0, 0.0);
const static QVector3D v_Y = QVector3D(0.0, 1.0, 0.0);
const static QVector3D v_Z = QVector3D(0.0, 0.0, 1.0);
const static QVector3D v_XY = QVector3D(1.0, 1.0, 0.0);
const static QVector3D v_XZ = QVector3D(1.0, 0.0, 1.0);
const static QVector3D v_YZ = QVector3D(0.0, 1.0, 1.0);
const static QVector3D v_XYZ = QVector3D(1.0, 1.0, 1.0);

/** Predefined global colors for convenience.
  */
const static GLColorRgba cl_White      = GLColorRgba(1.0,1.0,1.0);
const static GLColorRgba cl_Green      = GLColorRgba(0.0,1.0,0.0);
const static GLColorRgba cl_Blue       = GLColorRgba(0.0,0.0,1.0);
const static GLColorRgba cl_Red        = GLColorRgba(1.0,0.0,0.0);
const static GLColorRgba cl_Yellow     = GLColorRgba(1.0,1.0,0.0);
const static GLColorRgba cl_Lime       = GLColorRgba(106.0f/255.0f, 137.0f/255.0f, 65.0f/255.0f, 1.0f);
const static GLColorRgba cl_Turquoise    = GLColorRgba(55.0f/255.0f, 126.0f/255.0f, 126.0f/255.0f);
const static GLColorRgba cl_Sienna       = GLColorRgba(238.0f/255.0f, 121.0f/255.0f, 66.0f/255.0f);
const static GLColorRgba cl_Coral      = GLColorRgba(240.0f/255.0f, 128.0f/255.0f, 128.0f/255.0f);

#endif // GLDEFINES_H
