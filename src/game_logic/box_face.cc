//
//  box_face.cc
//  osx_unhinged
//
//  Created by Ben Lewis on 6/26/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "render/material.h"

#include "game_logic/box_face.h"
#include "game_logic/box.h"
#include "game_logic/facet.h"

BoxFace::BoxFace(FaceSide face_side, Box *box, Material *material) :
face_side_(face_side), box_(box), material_(material) {
  switch (face_side_) {
    case FACE_FRONT:
    case FACE_BACK:  box_->SetWidths(width_, draw_width_); box_->SetHeights(height_, draw_height_); break;
    case FACE_LEFT:
    case FACE_RIGHT: box_->SetLengths(width_, draw_width_); box_->SetHeights(height_, draw_height_); break;
    case FACE_TOP:
    case FACE_BOTTOM: box_->SetWidths(width_, draw_width_); box_->SetLengths(height_, draw_height_); break;
  }
  
  SetupFacets();
}

void BoxFace::Draw() {
  glPushMatrix();
  material_->EnableMaterial();
  GLfloat mult_width = 1.0f;
  GLfloat mult_height = 1.0f;
  
  switch (face_side_) {
    case FACE_FRONT: glNormal3d(0, 0, 1); break; // no rotate
    case FACE_BACK: glTranslatef(0.0f, 0.0f, -box_->get_draw_length());
      glRotatef(180.0f, 0.0f, 1.0f, 0.0f); glNormal3d(0, 0, -1); mult_width = -1.0f; break;
    case FACE_LEFT: glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); glNormal3d(-1, 0, 0); mult_width = -1.0f; break;
    case FACE_RIGHT: glTranslatef(box_->get_draw_width(), 0.0f, 0.0f);
      glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); glNormal3d(1, 0, 0); mult_width = -1.0f; break;
    case FACE_TOP: glTranslatef(0.0f, box_->get_draw_height(), 0.0f);
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); glNormal3d(0, 1, 0);  break;
    case FACE_BOTTOM: glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); glNormal3d(0, -1, 0);  break;
  }
  
  GLfloat dx = 0.0f; //box_->get_draw_x();
  GLfloat dy = 0.0f; //box_->get_draw_y();
  
  glBegin(GL_QUADS);
  glVertex2f(dx, dy);
  glVertex2f(dx + mult_width * draw_width_, dy);
  glVertex2f(dx + mult_width * draw_width_, dy + mult_height * draw_height_);
  glVertex2f(dx, dy + mult_height * draw_height_);
  glEnd();
  
  // Cycle through each facet and draw pegs and gears if necessary
  
  glPopMatrix();
}

void BoxFace::SetupFacets() {
  facets_.resize(width_);
  for (int i = 0; i < width_; i++) {
    facets_[i].resize(height_);
    for (int j = 0; j < height_; j++) {
      // Debug: set the front face to have pegs
      facets_[i][j] = new Facet((face_side_ == FACE_FRONT),
                                nullptr, this, i, j);
    }
  }
}