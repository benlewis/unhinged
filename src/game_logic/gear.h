//
//  gear.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__gear__
#define __osx_unhinged__gear__

#include "render/material.h"

enum Rotation {
	SPIN_CLOCKWISE,
	SPIN_COUNTERCLOCKWISE,
	SPIN_NONE
};

enum Plane {
  PLANE_XY,
  PLANE_XZ,
  PLANE_YZ
};

class Gear {
public:
	Gear(Rotation rotation, Material *material);

  void Update(int ticks);
	void Draw();

private:
  virtual void CreateList();
	GLfloat angle_ = 0.0f;
	Rotation rotation_;
  Material *material_;
  GLint list_; // for calling
  
};

#endif /* defined(__osx_unhinged__gear__) */
