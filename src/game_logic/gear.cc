//
//  gear.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "game_logic/gear.h"

#include "render/gl_headers.h"
#include "render/texture_manager.h"

#include "math.h"

Gear::Gear(Direction spin_direction, Material *material):
spin_direction_(spin_direction), material_(material)  {
  switch (spin_direction_) {
    case SPIN_CLOCKWISE:	angle_ = 0.0f; break;
    case SPIN_COUNTERCLOCKWISE:	angle_ = -6.5f; break;
    case SPIN_NONE: angle_ = 0.0f;
  }
  CreateList();
}

void Gear::Update(int ticks)
{
	switch (spin_direction_) {
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

	GLfloat inner_radius = 0.04f;
	GLfloat outer_radius = 0.094f;
	GLfloat width = 0.02f;
	GLint teeth = 10;
	GLfloat tooth_depth = 0.05f;
    
	GLint i;
  GLfloat r0, r1, r2;
  GLfloat angle, da;
  GLfloat u, v, len;
  
  r0 = inner_radius;
  r1 = outer_radius - tooth_depth / 2.0f;
  r2 = outer_radius + tooth_depth / 2.0f;
  
  da = 2.0f * M_PI / teeth / 4.0f;
  
  glShadeModel(GL_SMOOTH);
  
  glNormal3f(0.0f, 0.0f, 1.0f);

  
  /* draw front face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
      angle = i * 2.0f * M_PI / teeth;
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5f);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5f);
  }
  glEnd();
  
  /* draw front sides of teeth */
  glBegin(GL_QUADS);
  da = 2.0f * M_PI / teeth / 4.0f;
  for (i = 0; i < teeth; i++) {
      angle = i * 2.0f * M_PI / teeth;
      
      glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5f);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5f);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5f);
  }
  glEnd();
  
  glNormal3f(0.0f, 0.0f, -1.0f);
  
  /* draw back face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
      angle = i * 2.0f * M_PI / teeth;
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5f);
  }
  glEnd();
  
  /* draw back sides of teeth */
  glBegin(GL_QUADS);
  da = 2.0f * M_PI / teeth / 4.0f;
  for (i = 0; i < teeth; i++) {
      angle = i * 2.0f * M_PI / teeth;
      
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5f);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5f);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5f);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5f);
  }
  glEnd();
  
  /* draw outward faces of teeth */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < teeth; i++) {
      angle = i * 2.0f * M_PI / teeth;
      
      glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5f);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5f);
      u = r2 * cos(angle + da) - r1 * cos(angle);
      v = r2 * sin(angle + da) - r1 * sin(angle);
      len = sqrt(u * u + v * v);
      u /= len;
      v /= len;
      glNormal3f(v, -u, 0.0f);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5f);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5f);
      glNormal3f(cos(angle), sin(angle), 0.0);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5f);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5f);
      u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
      v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
      glNormal3f(v, -u, 0.0f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5f);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5f);
      glNormal3f(cos(angle), sin(angle), 0.0f);
  }
  
  glVertex3f(r1 * cos(0.0f), r1 * sin(0.0f), width * 0.5f);
  glVertex3f(r1 * cos(0.0f), r1 * sin(0.0f), -width * 0.5f);
  
  glEnd();
  
  glShadeModel(GL_SMOOTH);
  
  /* draw inside radius cylinder */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
      angle = i * 2.0f * M_PI / teeth;
      
      glNormal3f(-cos(angle), -sin(angle), 0.0f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5f);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5f);
  }
  glEnd();
  
	glEndList();
}