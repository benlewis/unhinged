//
//  box.cc
//  osx_unhinged
//
//  Created by Ben Lewis on 6/26/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "game_logic/box.h"
#include "game_logic/room.h"
#include "game_logic/box_face.h"

#include "render/material_manager.h"

Box::Box(int x, int y, int z, int width, int height, int length, Room *room):
x_(x), y_(y), z_(z), width_(width), height_(height), length_(length), room_(room) {
  
  draw_x_ = (GLfloat)x_ / room_->get_board_width() * room_->get_width() - room_->get_width() / 2.0f;
  draw_y_ = (GLfloat)y_ / room_->get_board_height() * room_->get_height() - room_->get_height() / 2.0f;
  draw_z_ = (GLfloat)z_ / room_->get_board_length() * room_->get_length() - room_->get_length() / 2.0f;
  
  draw_width_   = (GLfloat)width_ * room_->get_width() / room_->get_board_width();
  draw_height_  = (GLfloat)height_ * room_->get_height() / room_->get_board_height();
  draw_length_  = (GLfloat)length_ * room_->get_length() / room_->get_board_length();
  
  SetupFaces();
}

void Box::SetupFaces() {
  Material *mat = MaterialManager::Instance()->get_material("cyan_plastic");
  for (int i = 0; i < 6; i++) {
    faces_[i] = new BoxFace((FaceDirection)i, this, mat);
  }
  
}

void Box::Draw() {
//  if (draw_y_ >= 1.0f - draw_height_ && y_inc > 0.0f) {
//    y_inc *= -1.0f;
//  } else if (draw_y_ <= -1.0f && y_inc < 0.0f) {
//    y_inc *= -1.0f;
//  }
//  draw_y_ += y_inc;
  
  glPushMatrix();
  
  // Move to our bottom, left, front corner
  glTranslatef(draw_x_, draw_y_, draw_z_);
  
  // Then just draw every face. Each face rotates itself
  for (int i = 0; i < 6; i++) {
    faces_[i]->Draw();
  }
  
  glPopMatrix();
}

void Box::Clip(GLfloat x_old, GLfloat y_old, GLfloat z_old,
               GLfloat &x_new, GLfloat &y_new, GLfloat &z_new) {
  // TODO: Clip the box
}