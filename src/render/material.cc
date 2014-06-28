//
//  material.cc
//  osx_unhinged
//
//  Created by Ben Lewis on 6/25/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "render/material.h"

//
// Sets member variables based on the input data
// The format is defined in the material_XXXX #defines in the .h file
// This seems more efficient than storing the data in a file
//
Material::Material(GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat e, GLfloat f,
                   GLfloat g, GLfloat h, GLfloat i, GLfloat j, GLfloat k, GLfloat l,
                   GLfloat m) {
  ambient_[0]  = a; ambient_[1]  = b; ambient_[2]  = c; ambient_[3]  = d;
  diffuse_[0]  = e; diffuse_[1]  = f; diffuse_[2]  = g; diffuse_[3]  = h;
  specular_[0] = i / 5.0f; specular_[1] = j / 5.0f; specular_[2] = k / 5.0f; specular_[3] = l / 5.0f;
  
  shine_ = m;

}

void Material::EnableMaterial() {
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, ambient_);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diffuse_);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular_);
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shine_);
}