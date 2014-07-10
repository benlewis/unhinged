//
//  face.cc
//  osx_unhinged
//
//  Created by Ben Lewis on 6/26/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "render/material_manager.h"
#include "render/material.h"

#include "game_logic/room.h"
#include "game_logic/face.h"
#include "game_logic/facet.h"
#include "game_logic/gear.h"

Face::Face(Room *room, Material *material, string texture, int columns, int rows, glm::vec3 location, glm::vec4 rotation, Plane plane, bool facets) :
room_(room), material_(material), texture_name_(texture),
facets_columns_(columns), facets_rows_(rows),
location_(location), rotation_(rotation), plane_(plane) {
  
  SetupFacets(facets);
}

GLfloat Face::draw_width() {
  return room_->get_facet_size() * facets_columns_;
}

GLfloat Face::draw_height() {
  return room_->get_facet_size() * facets_rows_;
}

void Face::Draw() {
  glPushMatrix();
  if (material_) {
    material_->EnableMaterial();
  } else if (texture_name_ != "") {
    glEnable(GL_TEXTURE_2D);
    TextureManager::Instance()->BindTexture(texture_name_);
  }
  
  glTranslatef(location_.x, location_.y, location_.z);
  glRotatef(rotation_.w, rotation_.x, rotation_.y, rotation_.z);
  glNormal3d(0, 0, 1);
  
  GLfloat draw_width = this->draw_width();
  GLfloat draw_height = this->draw_height();
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex2f(-draw_width / 2.0f, -draw_height/2.0f);
  glTexCoord2f(2.0f, 0.0f); glVertex2f(draw_width / 2.0f, -draw_height/2.0f);
  glTexCoord2f(2.0f, 1.0f);
  glVertex2f(draw_width / 2.0f, draw_height/2.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(-draw_width / 2.0f, draw_height/2.0f);
  glEnd();
  
  if (texture_name_ != "") {
    glDisable(GL_TEXTURE_2D);
  }
  
  glTranslatef(-draw_width / 2.0f, -draw_height/2.0f, 0.0f);
  // Cycle through each facet and draw pegs and gears if necessary
  for (int i = 0; i < facets_columns_; i++) {
    for (int j = 0; j < facets_rows_; j++) {
      if (facets_[i][j]->HasPeg()) {
        glPushMatrix();
        glTranslatef(room_->get_facet_size() * i, room_->get_facet_size() * j, 0.0f);
        facets_[i][j]->Draw();
        glPopMatrix();
      }
    }
  }
  
  
  glPopMatrix();
}

Plane Face::get_plane() {
  return plane_;
}

void Face::Clip(glm::vec3 old_location, glm::vec3 &new_location) {

  glm::vec3 B1, B2, hit;
  GLfloat head_width = 0.15f;
  GLfloat head_height = 0.15f;
  
  switch (plane_) {
    case PLANE_XY:
      B1 = glm::vec3(location_.x - head_width - draw_width() / 1.98f,
                     location_.y - head_height - draw_height() / 1.98f,
                     location_.z - room_->get_clipping_plane());
      B2 = glm::vec3(B1.x + head_width + draw_width() * 1.04f,
                     B1.y + head_height + draw_height() * 1.04f,
                     B1.z + 2.0f * room_->get_clipping_plane());
      if (CheckLineBox(B1, B2, old_location, new_location, hit)) {
        new_location.z = old_location.z;
      }
      break;
    case PLANE_XZ:
      B1 = glm::vec3(location_.x - head_width - draw_width() / 1.98f,
                     location_.y - room_->get_clipping_plane(),
                     location_.z - head_height - draw_height() / 1.98);
      B2 = glm::vec3(B1.x + head_width + draw_width() * 1.04f,
                     B1.y + 2.0f * room_->get_clipping_plane(),
                     B1.z + head_height + draw_height() * 1.04f);
      if (CheckLineBox(B1, B2, old_location, new_location, hit)) {
        new_location.y = old_location.y;
      }
      break;
    case PLANE_YZ:
      B1 = glm::vec3(location_.x - room_->get_clipping_plane(),
                     location_.y - head_height - draw_height() / 1.98f,
                     location_.z - head_width - draw_width() / 1.98f);
      B2 = glm::vec3(B1.x + 2.0f * room_->get_clipping_plane(),
                     B1.y + head_height + draw_height() * 1.04f,
                     B1.z + head_width + draw_width() * 1.04f);
      if (CheckLineBox(B1, B2, old_location, new_location, hit)) {
        new_location.x = old_location.x;
      }

    break;
  }


}

void Face::SetupFacets(bool facets) {
  facets_.resize(facets_columns_);
  Material *peg_mat = MaterialManager::Instance()->get_material("obsidian");
  
  for (int i = 0; i < facets_columns_; i++) {
    facets_[i].resize(facets_rows_);
    for (int j = 0; j < facets_rows_; j++) {
      // This is the location of the exact center of the facet
      glm::vec3 facet_center;
      switch (plane_) {
        case PLANE_XY:
          facet_center.x = location_.x + room_->get_facet_size() * ((GLfloat)i + 0.5f);
          facet_center.y = location_.y + room_->get_facet_size() * ((GLfloat)j + 0.5f);
          facet_center.z = location_.z;
          break;
        case PLANE_XZ:
          facet_center.x = location_.x + room_->get_facet_size() * ((GLfloat)i + 0.5f);
          facet_center.y = location_.y;
          facet_center.z = location_.z + room_->get_facet_size() * ((GLfloat)j + 0.5f);
          break;
        case PLANE_YZ:
          facet_center.x = location_.x;
          facet_center.y = location_.y + room_->get_facet_size() * ((GLfloat)j + 0.5f);
          facet_center.z = location_.z + room_->get_facet_size() * ((GLfloat)i + 0.5f);
          break;
      }
      facets_[i][j] = new Facet(facets, this, room_, peg_mat, facet_center);
      if (facets && plane_ == PLANE_XY) {
        if (i == 0 && j == 0) {
          facets_[i][j]->AddGear(new Gear(SPIN_CLOCKWISE, MaterialManager::Instance()->get_material("bronze"),
                                          facets_[i][j]));
        } else {
          facets_[i][j]->AddGear(new Gear(SPIN_NONE, MaterialManager::Instance()->get_material("bronze"),
                                          facets_[i][j]));
        }
      }
    }
  }
}