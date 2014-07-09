//
//  render_math.h
//  osx_unhinged
//
//  Created by Ben Lewis on 7/9/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef osx_unhinged_render_math_h
#define osx_unhinged_render_math_h

#include "third_party/glm/glm.hpp"


enum Plane {
  PLANE_XY,
  PLANE_XZ,
  PLANE_YZ
};



/*
 A big thanks to http://www.3dkingdoms.com/weekly/weekly.php?a=3
*/

int inline GetIntersection( float fDst1, float fDst2, glm::vec3 P1, glm::vec3 P2, glm::vec3 &Hit);
int inline InBox( glm::vec3 Hit, glm::vec3 B1, glm::vec3 B2, const int Axis);
bool CheckLineBox( glm::vec3 B1, glm::vec3 B2, glm::vec3 L1, glm::vec3 L2, glm::vec3 &Hit);

#endif
