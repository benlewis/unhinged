//
//  box_face.cc
//  osx_unhinged
//
//  Created by Ben Lewis on 6/26/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "render/material_manager.h"
#include "render/material.h"

#include "game_logic/box_face.h"
#include "game_logic/box.h"
#include "game_logic/facet.h"
#include "game_logic/gear.h"

BoxFace::BoxFace(FaceDirection face_direction, Box *box, Material *material) :
face_direction_(face_direction), box_(box), material_(material) {
  switch (face_direction_) {
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
  
  switch (face_direction_) {
    case FACE_FRONT:
      break;
    case FACE_BACK:
      glTranslatef(box_->get_draw_width(), 0.0f, -box_->get_draw_length());
      glRotatef(180.0f, 0.0f, 1.0f, 0.0f); break;
    case FACE_LEFT:
      glTranslatef(0.0f, 0.0f, -box_->get_draw_length());
      glRotatef(-90.0f, 0.0f, 1.0f, 0.0f); break;
    case FACE_RIGHT:
      glTranslatef(box_->get_draw_width(), 0.0f, 0.0f);
      glRotatef(90.0f, 0.0f, 1.0f, 0.0f); break;
    case FACE_TOP:
      glTranslatef(0.0f, box_->get_draw_height(), 0.0f);
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); break;
    case FACE_BOTTOM:
      glTranslatef(0.0f, 0.0f, -box_->get_draw_length());
      glRotatef(90.0f, 1.0f, 0.0f, 0.0f); break;
  }
  
  glNormal3d(0, 0, 1);
  
  glBegin(GL_QUADS);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(draw_width_, 0.0f);
  glVertex2f(draw_width_, draw_height_);
  glVertex2f(0.0f, draw_height_);
  glEnd();
  
  // Cycle through each facet and draw pegs and gears if necessary
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      if (facets_[i][j]->HasPeg()) {
        glPushMatrix();
        glTranslatef(get_facet_width() * i, get_facet_height() * j, 0.0f);
        facets_[i][j]->Draw();
        glPopMatrix();
      }
    }
  }
  
  
  glPopMatrix();
}

void BoxFace::SetupFacets() {
  facets_.resize(width_);
  Material *peg_mat = MaterialManager::Instance()->get_material("obsidian");
  
  for (int i = 0; i < width_; i++) {
    facets_[i].resize(height_);
    for (int j = 0; j < height_; j++) {
      facets_[i][j] = new Facet(true,
                                nullptr,
                                this,
                                peg_mat,
                                i,
                                j);
    }
  }
}