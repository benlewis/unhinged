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

class Room
{
private:
  float left_wall = -1.0f, right_wall = 1.0f;
  float room_ceiling = 1.0f, room_floor = -1.0f;
  float front_wall = 2.0f, back_wall = -2.0f;
  float clipping_plane = 0.15f;
	float board_width = 20.0;
	float board_length = 10.0;
	float board_height = 10.0;

	vector<Piece*> pieces;
  
  void draw_face(vector<float> x, vector<float> y, vector<float> z);
  
public:
  Room();
  void clip(float &x, float &z);
  float get_width();
  float get_length();
  float get_height();
	float get_board_width();
	float get_board_length();
	float get_board_height();

  void draw();

};

#endif /* defined(__osx_unhinged__room__) */
