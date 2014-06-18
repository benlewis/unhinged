//
//  room.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__room__
#define __osx_unhinged__room__

#include "gl_headers.h"
#include "piece.h"

#include <stdlib.h>
#include <vector>

using namespace std;

class piece;

class room
{
private:
    float left_wall = -1.0f, right_wall = 1.0f;
    float room_ceiling = 1.0f, room_floor = -1.0f;
    float front_wall = 2.0f, back_wall = -2.0f;
    float clipping_plane = 0.15f;
	float board_width = 20.0;
	float board_length = 10.0;
	float board_height = 10.0;

	vector<piece*> pieces;

public:
    room();
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
