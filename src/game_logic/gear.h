//
//  gear.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__gear__
#define __osx_unhinged__gear__

#include "render/gl_headers.h"
#include "render/material.h"

class Facet;

enum Rotation {
	SPIN_CLOCKWISE,
	SPIN_COUNTERCLOCKWISE,
	SPIN_NONE
};

class Gear {
public:
	Gear(Rotation rotation, Material *material);

  void Update(int ticks);
	void Draw();
  GLfloat GetRadius();
  
  void ClearNextRotation();
  bool SetNextRotation(Rotation next_rotation);
  Rotation get_next_rotation() { return next_rotation_; }
  void EnableNextRotation();
  bool Intersects(Gear *g);
  Rotation OppositeRotation();
  
private:
  virtual void CreateList();
  GLint list_; // for calling
	
  Rotation rotation_; // What direction the gear is currentely spinning
  Rotation next_rotation_; // What direction the gear will spin after AddGear is complete
  Rotation base_rotation_; // Is this gear a Power gear? If so, it has a base spin.
	GLfloat angle_ = 0.0f;
  
  Facet *facet_;  
  Material *material_;
  
  // For drawing the gears and clipping
  GLfloat inner_radius_ = 0.04f;
	GLfloat outer_radius_ = 0.099f;
	GLfloat width_ = 0.02f;
	GLint teeth_ = 10;
	GLfloat tooth_depth_ = 0.038f;
  
};

#endif /* defined(__osx_unhinged__gear__) */
