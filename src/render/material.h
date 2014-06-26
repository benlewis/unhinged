//
//  material.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/25/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__material__
#define __osx_unhinged__material__

#include "render/gl_headers.h"

class Material {
private:
  GLfloat ambient_[4];
  GLfloat diffuse_[4];
  GLfloat specular_[4];
  GLfloat shine_;
  
  static float gold[];

public:
  Material(GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat e, GLfloat f, 
           GLfloat g, GLfloat h, GLfloat i, GLfloat j, GLfloat k, GLfloat l,
           GLfloat m);

  void EnableMaterial();

};

//
//
// A big thanks to http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
// For providing these materials
//
//

#define MATERIAL_GOLD \
    0.24725f, 0.1995f, 0.0745f, 1.0f, \
    0.75164f, 0.60648f, 0.22648f, 1.0f, \
    0.628281f, 0.555802f, 0.366065f, 1.0f, \
    51.2f

#define MATERIAL_BRONZE \
  0.329412f, 0.223529f, 0.027451f, 1.0f, \
  0.780392f, 0.568627f, 0.113725f, 1.0f, \
  0.992157f, 0.941176f, 0.807843f, 1.0f, \
  27.8974f

#endif /* defined(__osx_unhinged__material__) */
