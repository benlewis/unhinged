//
//  gl_headers.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef osx_unhinged_gl_headers_h
#define osx_unhinged_gl_headers_h

#ifdef __APPLE__
#include "OpenGL/gl.h"
#include "GLUT/glut.h"
#include <ApplicationServices/ApplicationServices.h>

#elif defined _WIN32 || defined _WIN64
#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#define M_PI 3.1415926f
#endif




#endif
