//
//  room.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "room.h"

room::room()
{
    // Room stuff
    // TODO: Move to the room file
    left_wall = -2.0f;
    right_wall = 2.0f;
    room_ceiling = 1.0f;
    room_floor = -1.0f;
    front_wall = 2.0f;
    back_wall = -2.0f;
    clipping_plane = 0.15f;
}

void room::draw()
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glShadeModel(GL_SMOOTH);
    /* Floor */
    glColor3f(1.0,1.0,1.0);
    glVertex3f(left_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,back_wall);
    glVertex3f(left_wall,room_floor,back_wall);
    /* Ceiling */
    glColor3f(0.55,0.55,0.55);
    glVertex3f(left_wall,room_ceiling,back_wall);
    glVertex3f(right_wall,room_ceiling,back_wall);
    glVertex3f(right_wall,room_ceiling,front_wall);
    glVertex3f(left_wall,room_ceiling,front_wall);
    /* Walls */
    glColor3f(0.35,0.35,0.35);
    glVertex3f(left_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_ceiling,front_wall);
    glVertex3f(left_wall,room_ceiling,front_wall);
    
    glVertex3f(left_wall,room_floor,back_wall);
    glVertex3f(right_wall,room_floor,back_wall);
    glVertex3f(right_wall,room_ceiling,back_wall);
    glVertex3f(left_wall,room_ceiling,back_wall);
    
    glColor3f(0.75,0.75,0.75);
    glVertex3f(right_wall,room_ceiling,front_wall);
    glVertex3f(right_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,back_wall);
    glVertex3f(right_wall,room_ceiling,back_wall);
    
    glVertex3f(left_wall,room_ceiling,front_wall);
    glVertex3f(left_wall,room_floor,front_wall);
    glVertex3f(left_wall,room_floor,back_wall);
    glVertex3f(left_wall,room_ceiling,back_wall);
    glEnd();
    
    glPopMatrix();
}

float room::get_width()
{
    return right_wall - left_wall;
}

float room::get_length()
{
    return front_wall - back_wall;
}

float room::get_height()
{
    return room_ceiling - room_floor;
}

void room::clip(float &x, float &z)
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
