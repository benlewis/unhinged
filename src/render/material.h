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
  friend class MaterialManager;

private:
  GLfloat ambient_[4];
  GLfloat diffuse_[4];
  GLfloat specular_[4];
  GLfloat shine_;
  
  static float gold[];

  Material(GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat e, GLfloat f,
           GLfloat g, GLfloat h, GLfloat i, GLfloat j, GLfloat k, GLfloat l,
           GLfloat m);

public:

  void EnableMaterial();

};

#endif /* defined(__osx_unhinged__material__) */
