//
//  face.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/26/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__face__
#define __osx_unhinged__face__

#include "render/gl_headers.h"

#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

class Facet;
class Room;
class Material;

class Face {
public:
  Face(Room *room, Material *material, string texture_name, int columns, int rows, glm::vec3 location, glm::vec4 rotation, Plane plane, bool facets = false);
  void Draw();
  Plane get_plane();
  void Clip(glm::vec3 old_location, glm::vec3 &new_location);
  
private:
  Room *room_;
  Material *material_;
  string texture_name_;
    
  // how many facets?
  Plane plane_; // XY, YX, XZ
  glm::vec3 location_;
  glm::vec4 rotation_;
  
  // Our facets on this face
  vector<vector<Facet*>> facets_;
  int facets_columns_, facets_rows_;
  void SetupFacets(bool facets);
  
  GLfloat draw_width();
  GLfloat draw_height();
};

#endif /* defined(__osx_unhinged__face__) */
