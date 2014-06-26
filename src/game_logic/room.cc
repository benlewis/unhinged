//
//  room.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "game_logic/room.h"
#include "render/material.h"

Room::Room() {
  // Establish parameters, probably should be in a configuration manager
  left_wall_ = -2.0f;
  right_wall_ = 2.0f;
  room_ceiling_ = 1.0f;
  room_floor_ = -1.0f;
  front_wall_ = 2.0f;
  back_wall_ = -2.0f;
  
  Material *gold = new Material(MATERIAL_GOLD);
  Material *bronze = new Material(MATERIAL_BRONZE);
  
	pieces_.push_back(new Gear(10, 5, 5, this, SPIN_CLOCKWISE, 0.0f, gold));
	pieces_.push_back(new Gear(11, 5, 5, this, SPIN_COUNTERCLOCKWISE, -8.0f, bronze));
	pieces_.push_back(new Gear(12, 5, 5, this, SPIN_CLOCKWISE, 0.0f, gold));
}

void Room::Draw() {
  GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  
  GLfloat lightColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat lightPos[] = {0.0f, 0.0f, -2.0f, 1.0f};
  GLfloat backPos[] = {0.0f, 0.0f, 2.0f, 1.0f};
  GLfloat backDir[] = {0.0f, 0.0f, -1.0f, 1.0f};

  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos);

  glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT2, GL_SPECULAR, lightColor);
  glLightfv(GL_LIGHT2, GL_POSITION, backPos);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, backDir);
  
  glPushMatrix();
  glShadeModel(GL_SMOOTH);

  DrawFace({ right_wall_ }, { room_floor_, room_ceiling_ }, { front_wall_, back_wall_ } );
  DrawFace({ left_wall_ }, { room_floor_, room_ceiling_ }, { front_wall_, back_wall_ });
  
  DrawFace({ right_wall_, left_wall_ }, { room_floor_ }, { front_wall_, back_wall_ });
  DrawFace({ right_wall_, left_wall_ }, { room_ceiling_ }, { front_wall_, back_wall_ });
  
  DrawFace({ right_wall_, left_wall_ }, { room_floor_, room_ceiling_ }, { front_wall_ });
  DrawFace({ right_wall_, left_wall_ }, { room_floor_, room_ceiling_ }, { back_wall_ });
  
  glPopMatrix();

  vector<Piece*>::iterator it;
  for (it = pieces_.begin(); it != pieces_.end(); ++it) {
    Piece *piece = *it;
    piece->Update(0);
    piece->Draw();
  }

  
}

void Room::DrawFace(vector<float> x, vector<float> y, vector<float> z)
{
  GLfloat tex_x = 0.0f;
  GLfloat tex_y = 0.0f;
  int step = 0;
  
  glEnable(GL_TEXTURE_2D);
  TextureManager::Instance()->BindTexture("darkwood.jpg");
  glBegin(GL_QUADS);
  for (vector<float>::iterator i = x.begin(); i != x.end(); ++i) {
    for (vector<float>::iterator j = y.begin(); j != y.end(); ++j) {
      for (vector<float>::iterator k = z.begin(); k != z.end(); ++k) {
        glTexCoord2f(tex_x, tex_y); glVertex3f(*i, *j, *k);
        switch (step++) {
          case 0: tex_x = 2.0; break;
          case 1: tex_y = 1.0; break;
          case 2: tex_x = 0.0; break;
          case 3: tex_y = 0.0; break;
        }
      }
      reverse(z.begin(), z.end());
    }
    reverse(y.begin(), y.end());
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

GLfloat Room::get_width() {
    return right_wall_ - left_wall_;
}

GLfloat Room::get_length() {
    return front_wall_ - back_wall_;
}

GLfloat Room::get_height() {
    return room_ceiling_ - room_floor_;
}

GLfloat Room::get_board_width() {
	return board_width_;
}

GLfloat Room::get_board_length() {
	return board_length_;
}

GLfloat Room::get_board_height() {
	return board_height_;
}

void Room::Clip(GLfloat &x, GLfloat &z) {
    if (x < left_wall_ + clipping_plane_)
        x = left_wall_ + clipping_plane_;
    if (x > right_wall_ - clipping_plane_)
        x = right_wall_ - clipping_plane_;
    if (z > front_wall_ - clipping_plane_)
        z = front_wall_ - clipping_plane_;
    if (z < back_wall_ + clipping_plane_)
        z = back_wall_ + clipping_plane_;
}
