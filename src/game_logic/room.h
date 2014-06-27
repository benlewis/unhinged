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
class Box;

class Room {
private:
  GLfloat left_wall_, right_wall_;
  GLfloat room_ceiling_, room_floor_;
  GLfloat front_wall_, back_wall_;
  
  GLfloat clipping_plane_ = 0.15f;
	GLfloat board_width_ = 20.0f;
	GLfloat board_length_ = 10.0f;
	GLfloat board_height_ = 10.0f;

	vector<Piece*> pieces_;
  Box *box_;
  
  void DrawFace(vector<float> x, vector<float> y, vector<float> z);
  
public:
  Room();
  void Clip(GLfloat &x, GLfloat &z);
  GLfloat get_width();
  GLfloat get_length();
  GLfloat get_height();
	GLfloat get_board_width();
	GLfloat get_board_length();
	GLfloat get_board_height();

  void Draw();

};

#endif /* defined(__osx_unhinged__room__) */
