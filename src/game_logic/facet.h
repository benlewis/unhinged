//
//  facet.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/24/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__facet__
#define __osx_unhinged__facet__

#include "render/gl_headers.h"
#include <stdlib.h>
#include <string>

class Gear;
class Face;
class Material;
class Room;

class Facet {
public:
  Facet(bool peg, Face *face, Room *room, Material *peg_material, glm::vec3 location):
    peg_(peg), gear_(nullptr), face_(face), peg_material_(peg_material), location_(location), room_(room) {}
  bool AddGear(Gear* gear);
  void RemoveGear(Gear* gear);
  bool HasGear();
  bool HasPeg() { return peg_; }
  void Draw();
  
  glm::vec3 get_location() { return location_; }
  Plane get_plane();
  
private:
  bool peg_; // Can this hold a gear?
  Material *peg_material_;
  Gear *gear_; // Can be null if no gear
  
  Face *face_; // What box face this lives on
  Room *room_; // Used for getting facet_size and for AddGear
  
  // Real location
  glm::vec3 location_;
};

#endif /* defined(__osx_unhinged__facet__) */