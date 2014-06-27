//
//  facet.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/24/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__facet__
#define __osx_unhinged__facet__

class Gear;
class BoxFace;

class Facet {
public:
  Facet(bool peg, Gear *gear, BoxFace *box_face, int x, int y):
    peg_(peg), gear_(gear), box_face_(box_face), x_(x), y_(y) {};
  bool AddGear(Gear* gear);
  void RemoveGear(Gear* gear);
  bool HasGear();

private:
  bool peg_; // Can this hold a gear?
  Gear *gear_; // Can be null if no gear
  
  BoxFace *box_face_; // What box face this lives on
  int x_, y_; // Where this is in the facets_ 2d array of the box face
};

#endif /* defined(__osx_unhinged__facet__) */