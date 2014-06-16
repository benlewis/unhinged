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

class room
{
private:
    float left_wall = -1.0f, right_wall = 1.0f;
    float room_ceiling = 1.0f, room_floor = -1.0f;
    float front_wall = 2.0f, back_wall = -2.0f;
    float clipping_plane = 0.15f;
    
public:
    room();
    void clip(float &x, float &z);
    float get_width();
    float get_length();
    float get_height();
    
    void draw();

};

#endif /* defined(__osx_unhinged__room__) */
