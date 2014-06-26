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
  GLfloat *ambient_;
  GLfloat *diffuse_;
  GLfloat *specular_;
  GLfloat shine_;
  
  static float gold[];

public:
  Material(GLfloat *input_data);
  void EnableMaterial();

};
#endif /* defined(__osx_unhinged__material__) */
