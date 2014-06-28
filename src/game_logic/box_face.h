//
//  box_face.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/26/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__box_face__
#define __osx_unhinged__box_face__

#include "render/gl_headers.h"

#include <stdlib.h>
#include <vector>

using namespace std;

class Facet;
class Box;
class Material;

enum FaceSide {
  FACE_FRONT = 0,
  FACE_BACK,
  FACE_LEFT,
  FACE_RIGHT,
  FACE_TOP,
  FACE_BOTTOM
};

class BoxFace {
public:
  BoxFace(FaceSide face_side, Box *box, Material *material);
  void Draw();
  GLfloat get_facet_width() { return draw_width_ / (GLfloat)width_; }
  GLfloat get_facet_height() { return draw_height_ / (GLfloat)height_; }
  
private:
  // What other faces do we touch
  // This is needed for gears on the edges
  BoxFace *face_above_, *face_below_;
  BoxFace *face_left_, *face_right_;
  
  Box *box_;
  Material *material_;
  
  FaceSide face_side_;
  
  // size in game space
  int width_, height_;
  GLfloat draw_width_, draw_height_;
  
  // Our facets on this face
  vector<vector<Facet*>> facets_;
  void SetupFacets();
};

#endif /* defined(__osx_unhinged__box_face__) */
