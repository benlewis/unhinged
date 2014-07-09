//
//  gear.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "game_logic/gear.h"
#include "game_logic/facet.h"

#include "render/gl_headers.h"
#include "render/texture_manager.h"

#include "math.h"

Gear::Gear(Rotation base_rotation, Material *material):
base_rotation_(base_rotation), material_(material)  {
  CreateList();
}

void Gear::Update(int ticks)
{
	switch (rotation_) {
	case SPIN_CLOCKWISE:		angle_ -= 1.0f; break;
	case SPIN_COUNTERCLOCKWISE:	angle_ += 1.0f; break;
	case SPIN_NONE: break;
	}
}

void Gear::Draw()
{
	glPushMatrix();
	glRotatef(this->angle_, 0.0f, 0.0f, 1.0f);
	glCallList(list_);
	glPopMatrix();
}

GLfloat Gear::GetRadius() {
  return outer_radius_ + tooth_depth_;
}

void Gear::ClearNextRotation() {
  next_rotation_ = base_rotation_;
}

void Gear::EnableNextRotation() {
  rotation_ = next_rotation_;
  
  // Offset the angle a bit to make it look like the gears interlock
  switch (rotation_) {
    case SPIN_CLOCKWISE:	angle_ = 0.0f; break;
    case SPIN_COUNTERCLOCKWISE:	angle_ = -6.5f; break;
    case SPIN_NONE: angle_ = 0.0f;
  }
}

Rotation Gear::OppositeRotation() {
  switch (next_rotation_) {
    case SPIN_NONE: return SPIN_NONE; break;
    case SPIN_CLOCKWISE: return SPIN_COUNTERCLOCKWISE; break;
    case SPIN_COUNTERCLOCKWISE: return SPIN_CLOCKWISE; break;
  }
}

bool Gear::Intersects(Gear *g) {
  glm::vec3 my_location = facet_->get_location();
  glm::vec3 location = g->facet_->get_location();
  
  
  if (facet_->get_plane() == g->facet_->get_plane()) {
    // Since we are the same plane direction, make sure it's the same plane
    switch (facet_->get_plane()) {
      case PLANE_XY: if (location.z != my_location.z) { return false; } break;
      case PLANE_XZ: if (location.y != my_location.y) { return false; } break;
      case PLANE_YZ: if (location.x != my_location.x) { return false; } break;
    }
  }
  
  // I could make this more accurate, but there's no need for now
  
  if (glm::distance(my_location, location) < GetRadius() + g->GetRadius()) {
    return true;
  } else {
    return false;
  }
}

bool Gear::SetNextRotation(Rotation next_rotation) {
  if (next_rotation_ == SPIN_NONE || next_rotation_ == next_rotation) {
    next_rotation_ = next_rotation;
    return true;
  } else {
    // A gear can't spin in two directions
    return false;
  }
}

/*
  A big thank you to Brian Paul from
  http://www.opengl.org/archives/resources/code/samples/glut_examples/mesademos/gears.c
 
  I added in the materials, but he did the actual Gear creation
*/
void Gear::CreateList()
{
	list_ = glGenLists(1);
	glNewList(list_, GL_COMPILE);
  
  material_->EnableMaterial();


    
	GLint i;
  GLfloat r0, r1, r2;
  GLfloat angle, da;
  GLfloat u, v, len;
  
  r0 = inner_radius_;
  r1 = outer_radius_ - tooth_depth_ / 2.0f;
  r2 = outer_radius_ + tooth_depth_ / 2.0f;
  
  da = 2.0f * M_PI / teeth_ / 4.0f;
  
  glShadeModel(GL_SMOOTH);
  
  glNormal3f(0.0f, 0.0f, 1.0f);

  
  /* draw front face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth_; i++) {
      angle = i * 2.0f * M_PI / teeth_;
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width_ * 0.5f);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), width_ * 0.5f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width_ * 0.5f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width_ * 0.5f);
  }
  glEnd();
  
  /* draw front sides of teeth_ */
  glBegin(GL_QUADS);
  da = 2.0f * M_PI / teeth_ / 4.0f;
  for (i = 0; i < teeth_; i++) {
      angle = i * 2.0f * M_PI / teeth_;
      
      glVertex3f(r1 * cos(angle), r1 * sin(angle), width_ * 0.5f);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width_ * 0.5f);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width_ * 0.5f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width_ * 0.5f);
  }
  glEnd();
  
  glNormal3f(0.0f, 0.0f, -1.0f);
  
  /* draw back face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth_; i++) {
      angle = i * 2.0f * M_PI / teeth_;
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width_ * 0.5f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width_ * 0.5f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width_ * 0.5f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width_ * 0.5f);
  }
  glEnd();
  
  /* draw back sides of teeth_ */
  glBegin(GL_QUADS);
  da = 2.0f * M_PI / teeth_ / 4.0f;
  for (i = 0; i < teeth_; i++) {
      angle = i * 2.0f * M_PI / teeth_;
      
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width_ * 0.5f);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width_ * 0.5f);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width_ * 0.5f);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width_ * 0.5f);
  }
  glEnd();
  
  /* draw outward faces of teeth_ */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < teeth_; i++) {
      angle = i * 2.0f * M_PI / teeth_;
      
      glVertex3f(r1 * cos(angle), r1 * sin(angle), width_ * 0.5f);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width_ * 0.5f);
      u = r2 * cos(angle + da) - r1 * cos(angle);
      v = r2 * sin(angle + da) - r1 * sin(angle);
      len = sqrt(u * u + v * v);
      u /= len;
      v /= len;
      glNormal3f(v, -u, 0.0f);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width_ * 0.5f);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width_ * 0.5f);
      glNormal3f(cos(angle), sin(angle), 0.0);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width_ * 0.5f);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width_ * 0.5f);
      u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
      v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
      glNormal3f(v, -u, 0.0f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width_ * 0.5f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width_ * 0.5f);
      glNormal3f(cos(angle), sin(angle), 0.0f);
  }
  
  glVertex3f(r1 * cos(0.0f), r1 * sin(0.0f), width_ * 0.5f);
  glVertex3f(r1 * cos(0.0f), r1 * sin(0.0f), -width_ * 0.5f);
  
  glEnd();
  
  glShadeModel(GL_SMOOTH);
  
  /* draw inside radius cylinder */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth_; i++) {
      angle = i * 2.0f * M_PI / teeth_;
      
      glNormal3f(-cos(angle), -sin(angle), 0.0f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width_ * 0.5f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width_ * 0.5f);
  }
  glEnd();
  
	glEndList();
}