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
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0.0f, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex2f(draw_width, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex2f(draw_width, draw_height);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0.0f, draw_height);
  glEnd();
  
  if (texture_name_ != "") {
    glDisable(GL_TEXTURE_2D);
  }

  
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
  switch (plane_) {
    case PLANE_XY:
      if (rotation_.w == 0.0f) {
        if (old_location.x > location_.x && old_location.x < location_.x + draw_width() &&
            new_location.x > location_.x && new_location.x < location_.x + draw_width() &&
            old_location.y > location_.y && old_location.y < location_.y + draw_height() &&
            new_location.y > location_.y && new_location.y < location_.y + draw_height() &&
            old_location.z > location_.z - room_->get_clipping_plane() &&
            new_location.z <= location_.z + room_->get_clipping_plane()) {
          new_location.z = location_.z + room_->get_clipping_plane();
        }
      } else {
        printf("Checking clip of %.2f,%.2f,%.2f to %.2f,%.2f,%.2f\n", old_location.x, old_location.y, old_location.z, new_location.x, new_location.y, new_location.z);
        printf("Checking clip of %.2f,%.2f,%.2f to %.2f,%.2f,%.2f\n", location_.x, location_.y, location_.z, new_location.x, new_location.y, new_location.z);
        if (old_location.x < location_.x && old_location.x > location_.x - draw_width() &&
            new_location.x < location_.x && new_location.x > location_.x - draw_width() &&
            old_location.y > location_.y && old_location.y < location_.y + draw_height() &&
            new_location.y > location_.y && new_location.y < location_.y + draw_height() &&
            old_location.z < location_.z + room_->get_clipping_plane() &&
            new_location.z >= location_.z - room_->get_clipping_plane()) {
          new_location.z = location_.z - room_->get_clipping_plane();
        }
      }
      break;
    case PLANE_XZ:
      break;
    case PLANE_YZ:
      break;
  }
  
  //  glm::vec3 B1, B2;
//  switch (plane_) {
//    case PLANE_XY:
//      B1 = glm::vec3(location_.x,
//                     location_.y,
//                     location_.z + room_->get_clipping_plane());
//      B2 = glm::vec3(location_.x + room_->get_facet_size() * facets_columns_,
//                     location_.y + room_->get_facet_size() * facets_rows_,
//                     location_.z - room_->get_clipping_plane());
//      if (texture_name_ != "") {
//      printf("Checking clip of %.2f,%.2f,%.2f to %.2f,%.2f,%.2f %.2f,%.2f,%.2f to %.2f,%.2f,%.2f\n", B1.x, B1.y, B1.z, B2.x, B2.y, B2.z, old_location.x, old_location.y, old_location.z, new_location.x, new_location.y, new_location.z);
//      }
//      break;
//    case PLANE_XZ:
//      B1 = glm::vec3(location_.x - room_->get_facet_size() * facets_columns_ / 2.0f,
//                     location_.z - room_->get_facet_size() * facets_rows_ / 2.0f,
//                     location_.y + room_->get_clipping_plane());
//      B2 = glm::vec3(location_.x + room_->get_facet_size() * facets_columns_ / 2.0f,
//                     location_.z + room_->get_facet_size() * facets_rows_ / 2.0f,
//                     location_.y - room_->get_clipping_plane());
//      break;
//    case PLANE_YZ:
//      B1 = glm::vec3(location_.z - room_->get_facet_size() * facets_columns_ / 2.0f,
//                     location_.y - room_->get_facet_size() * facets_rows_ / 2.0f,
//                     location_.x + room_->get_clipping_plane());
//      B2 = glm::vec3(location_.z + room_->get_facet_size() * facets_columns_ / 2.0f,
//                     location_.y + room_->get_facet_size() * facets_rows_ / 2.0f,
//                     location_.x - room_->get_clipping_plane());
//    break;
//  }
//
//
//  
//  if (CheckLineBox(B1, B2, old_location, new_location, new_location)) {
//    printf("Clipped!\n");
//    new_location = old_location;
//  }
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
    }
  }
}