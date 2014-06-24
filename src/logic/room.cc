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
  glPushMatrix();
  glShadeModel(GL_SMOOTH);

  /* Floor */
  glEnable(GL_TEXTURE_2D);
  TextureManager::Instance()->BindTexture("darkwood.jpg");
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(left_wall,room_floor,front_wall);
  glTexCoord2f(3.0f, 0.0f); glVertex3f(right_wall,room_floor,front_wall);
  glTexCoord2f(3.0f, 1.0f); glVertex3f(right_wall,room_floor,back_wall);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(left_wall,room_floor,back_wall);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  
  /* Ceiling */
  glEnable(GL_TEXTURE_2D);
  TextureManager::Instance()->BindTexture("darkwood.jpg");
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(left_wall,room_ceiling,back_wall);
  glTexCoord2f(4.0f, 0.0f); glVertex3f(right_wall,room_ceiling,back_wall);
  glTexCoord2f(4.0f, 1.0f); glVertex3f(right_wall,room_ceiling,front_wall);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(left_wall,room_ceiling,front_wall);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  /* Walls */
  glEnable(GL_TEXTURE_2D);
  TextureManager::Instance()->BindTexture("darkwood.jpg");
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(left_wall,room_floor,front_wall);
  glTexCoord2f(2.0f, 0.0f); glVertex3f(right_wall,room_floor,front_wall);
  glTexCoord2f(2.0f, 1.0f); glVertex3f(right_wall,room_ceiling,front_wall);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(left_wall,room_ceiling,front_wall);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  glEnable(GL_TEXTURE_2D);
  TextureManager::Instance()->BindTexture("darkwood.jpg");
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(left_wall,room_floor,back_wall);
  glTexCoord2f(2.0f, 0.0f); glVertex3f(right_wall,room_floor,back_wall);
  glTexCoord2f(2.0f, 1.0f); glVertex3f(right_wall,room_ceiling,back_wall);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(left_wall,room_ceiling,back_wall);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  glEnable(GL_TEXTURE_2D);
  TextureManager::Instance()->BindTexture("darkwood.jpg");
  glBegin(GL_QUADS);
  glTexCoord2f(2.0f, 1.0f); glVertex3f(right_wall,room_ceiling,front_wall);
  glTexCoord2f(2.0f, 0.0f); glVertex3f(right_wall,room_floor,front_wall);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(right_wall,room_floor,back_wall);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(right_wall,room_ceiling,back_wall);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  glEnable(GL_TEXTURE_2D);
  TextureManager::Instance()->BindTexture("darkwood.jpg");
  glBegin(GL_QUADS);
  glTexCoord2f(2.0f, 1.0f); glVertex3f(left_wall,room_ceiling,front_wall);
  glTexCoord2f(2.0f, 0.0f); glVertex3f(left_wall,room_floor,front_wall);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(left_wall,room_floor,back_wall);
  glTexCoord2f(0.0f, 1.0f); glVertex3f(left_wall,room_ceiling,back_wall);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  
  glPopMatrix();

  vector<Piece*>::iterator it;
  for (it = pieces.begin(); it != pieces.end(); ++it) {
    Piece *piece = *it;
    piece->update(0);
    piece->draw();
  }

  
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
