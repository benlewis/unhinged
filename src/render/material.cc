//
//  material.cc
//  osx_unhinged
//
//  Created by Ben Lewis on 6/25/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "render/material.h"


//
//
// A big thanks to http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
// For providing these materials
//
//

GLfloat* material_gold() {
  GLfloat mat[13] = {
    0.24725f, 0.1995f, 0.0745f, 1.0f, // ambient
    0.75164f, 0.60648f, 0.22648f, 1.0f, // diffuse
    0.628281f, 0.555802f, 0.366065f, 1.0f, // specular
    51.2f}; // shines
  
  return mat;
}

constexpr static GLfloat material_bronze[13] = {
  0.329412f, 0.223529f, 0.027451f, 1.0f,
  0.780392f, 0.568627f, 0.113725f, 1.0f,
  0.992157f, 0.941176f, 0.807843f, 1.0f,
  27.8974f};

//
// Sets member variables based on the input data
// The format is defined in the material_XXXX consts in the .h file
// This seems more efficient than storing the data in a file
//
Material::Material(GLfloat *input_data) {
  this->ambient_  = &input_data[0];
  this->diffuse_  = &input_data[4 * sizeof(GLfloat)];
  this->specular_ = &input_data[8 * sizeof(GLfloat)];
  this->shine_    = input_data[12 * sizeof(GLfloat)];
}

void Material::EnableMaterial() {
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, ambient_);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diffuse_);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular_);
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shine_);
}