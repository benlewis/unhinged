//
//  box.h
//  osx_unhinged
//
//  A box is where the game takes place
//
//  Created by Ben Lewis on 6/26/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__box__
#define __osx_unhinged__box__

#include "render/gl_headers.h"


#include <stdlib.h>
#include <array>

using namespace std;

class BoxFace;
class Room;

class Box {
public:
	Box(int x, int y, int z, int width, int height, int length, Room *room);
  void Draw();
  void Clip(GLfloat x_old, GLfloat y_old, GLfloat z_old,
            GLfloat &x_new, GLfloat &y_new, GLfloat &z_new);
  int get_width() { return width_; }
  int get_height() { return height_; }
  int get_length() { return length_; }
  
  GLfloat get_draw_width() { return draw_width_; }
  GLfloat get_draw_height() { return draw_height_; }
  GLfloat get_draw_length() { return draw_length_; }
  GLfloat get_draw_x() { return draw_x_; }
  GLfloat get_draw_y() { return draw_y_; }
  GLfloat get_draw_z() { return draw_z_; }
  
  
  void SetWidths(int &width, GLfloat &draw_width) { width = width_; draw_width = draw_width_; }
  void SetHeights(int &height, GLfloat &draw_height) { height = height_; draw_height = draw_height_; }
  void SetLengths(int &length, GLfloat &draw_length) { length = length_; draw_length = draw_length_; }
  
private:
  Room *room_; // our game room
  int x_, y_, z_; // the game block left, bottom, back location of the box
  int width_, height_, length_; // the size of the block in game space
  GLfloat draw_x_, draw_y_, draw_z_; // where we start drawing in screen space
  GLfloat draw_width_, draw_height_, draw_length_; // drawing in real space

  /*
   Our faces contain facets and handle the drawing
  */
  array<BoxFace*, 6> faces_; // all facets live on a side of our box
  
  void SetupFaces();
  
  // For animation
  GLfloat y_inc = 0.01f;
  
};
#endif /* defined(__osx_unhinged__box__) */
