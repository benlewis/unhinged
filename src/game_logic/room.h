//
//  room.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__room__
#define __osx_unhinged__room__

#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "render/gl_headers.h"
#include "render/texture_manager.h"

#include "third_party/SOIL/SOIL.h"

#include "game_logic/piece.h"
#include "game_logic/gear.h"


using namespace std;

class Piece;

class Room {
private:
  GLfloat left_wall, right_wall;
  GLfloat room_ceiling, room_floor;
  GLfloat front_wall, back_wall;
  
  GLfloat clipping_plane = 0.15f;
	GLfloat board_width = 20.0f;
	GLfloat board_length = 10.0f;
	GLfloat board_height = 10.0f;

	vector<Piece*> pieces;
  
  void draw_face(vector<float> x, vector<float> y, vector<float> z);
  
public:
  Room();
  void clip(GLfloat &x, GLfloat &z);
  GLfloat get_width();
  GLfloat get_length();
  GLfloat get_height();
	GLfloat get_board_width();
	GLfloat get_board_length();
	GLfloat get_board_height();

  void draw();

};

#endif /* defined(__osx_unhinged__room__) */
