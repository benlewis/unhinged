//
//  room.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "room.h"
#include "gear.h"
#include "texture_manager.h"
#include "SOIL/SOIL.h"

#include <algorithm>

Room::Room()
{
    // Establish parameters, probably should be in a configuration manager
    left_wall = -2.0f;
    right_wall = 2.0f;
    room_ceiling = 1.0f;
    room_floor = -1.0f;
    front_wall = 2.0f;
    back_wall = -2.0f;
    clipping_plane = 0.15f;
    
	pieces.push_back(new Gear(10, 5, 5, this, SPIN_CLOCKWISE, 0.0f));
	pieces.push_back(new Gear(11, 5, 5, this, SPIN_COUNTERCLOCKWISE, -8.0f));
	pieces.push_back(new Gear(12, 5, 5, this, SPIN_CLOCKWISE, 0.0f));
}

void Room::draw()
{
  GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  
  GLfloat lightColor[] = {0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat lightPos[] = {0.0f, 0.0f, 2.0f, 1.0f};
  GLfloat backPos[] = {0.0f, 0.0f, -1.5f, 1.0f};
  GLfloat backDir[] = {0.0f, 0.0f, -1.0f, 1.0f};

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor);
  glLightfv(GL_LIGHT1, GL_POSITION, backPos);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, backDir);
  
  glPushMatrix();
  glShadeModel(GL_SMOOTH);

  draw_face({ right_wall }, { room_floor, room_ceiling }, { front_wall, back_wall } );
  draw_face({ left_wall }, { room_floor, room_ceiling }, { front_wall, back_wall } );
  
  draw_face({ right_wall, left_wall }, { room_floor }, { front_wall, back_wall });
  draw_face({ right_wall, left_wall }, { room_ceiling }, { front_wall, back_wall });
  
  draw_face({ right_wall, left_wall }, { room_floor, room_ceiling }, { front_wall });
  draw_face({ right_wall, left_wall }, { room_floor, room_ceiling }, { back_wall });
  
  glPopMatrix();

  vector<Piece*>::iterator it;
  for (it = pieces.begin(); it != pieces.end(); ++it) {
    Piece *piece = *it;
    piece->update(0);
    piece->draw();
  }

  
}

void Room::draw_face(vector<float> x, vector<float> y, vector<float> z)
{
  float tex_x = 0.0f;
  float tex_y = 0.0f;
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

float Room::get_width()
{
    return right_wall - left_wall;
}

float Room::get_length()
{
    return front_wall - back_wall;
}

float Room::get_height()
{
    return room_ceiling - room_floor;
}

float Room::get_board_width()
{
	return board_width;
}

float Room::get_board_length()
{
	return board_length;
}

float Room::get_board_height()
{
	return board_height;
}

void Room::clip(float &x, float &z)
{
    if (x < left_wall + clipping_plane)
        x = left_wall + clipping_plane;
    if (x > right_wall - clipping_plane)
        x = right_wall - clipping_plane;
    if (z > front_wall - clipping_plane)
        z = front_wall - clipping_plane;
    if (z < back_wall + clipping_plane)
        z = back_wall + clipping_plane;
}
