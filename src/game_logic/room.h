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

#include "game_logic/gear.h"


using namespace std;

class Face;
class Gear;

class Room {
private:
  // TODO: Put these into a configuration file
  
  // Don't go right up against walls or blocks
  GLfloat clipping_plane_ = 0.15f;
  
  // The room dimensions. Assume middle at 0.0f
	GLfloat width_    = 4.0f;
	GLfloat length_   = 4.0f;
	GLfloat height_   = 2.0f;
  
  // How big is a facet
  GLfloat facet_size_     = 0.25f;

  vector<Face*> faces_; // All the faces we will draw
  vector<Gear*> gears_; // All our gears, for tracking spins
  
  void CreateRoomWalls();
  void CreateBox(glm::vec3 box_center, GLint w, GLint h, GLint l);
  
public:
  Room();
  void Clip(glm::vec3 old_location, glm::vec3 &new_location);
  void Draw();
  bool AddGear(Gear *gear);
  GLfloat get_clipping_plane() { return clipping_plane_; }
  GLfloat get_facet_size() { return facet_size_; }
};

#endif /* defined(__osx_unhinged__room__) */
