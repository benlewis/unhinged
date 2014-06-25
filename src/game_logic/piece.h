//
//  piece.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//
//  This is the super class for all drawable game pieces
//  The methods handle clipping and drawing
//  And loading obj files from a blender export
//
//  This is a virtual class - there can only be
//  instances of inherited classes

/*
 Gears:
    - Circle
    - Size == radius
    - Doesn't take up a whole "block" of game space
    - Not clippable (should be close enough to the Blocks)
    - Can only live on spokes (but can be in inventory, in hand)
 
 Spokes:
    - Live on the faces of Blocks
    - Not clippable
    - Fairly uniform
 
 Blocks:
    - Clippable
    - Take up a single game block of space
    - Has up to 6 faces, not all of which are outward facing

 Walls:
    - Single face
    - Clippable
    - One has a door
*/


#ifndef __osx_unhinged__piece__
#define __osx_unhinged__piece__

#include "render/gl_headers.h"

class Room;

class Piece {
public:
	Piece(int x, int y, int z, Room *gr);
  virtual void draw();
  virtual void update(int ticks);
  void clip(float x_old, float y_old, float &x_new, float &y_new);
    
protected:
  int x_, y_, z_; // the game block location of the pice
  GLfloat draw_x_, draw_y_, draw_z_; // where we start drawing in screen space
  GLint list_; // for speedy drawing with glCallList
	virtual void create_list() {}

};

#endif /* defined(__osx_unhinged__piece__) */
