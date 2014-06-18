//
//  gear.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__gear__
#define __osx_unhinged__gear__

#include <iostream>
#include "piece.h"
#include "gl_headers.h"
#include "math.h"

class gear : public piece
{
public:
    void list(GLfloat inner_radius, GLfloat outer_radius, GLfloat width,
              GLint teeth, GLfloat tooth_depth);
};
#endif /* defined(__osx_unhinged__gear__) */
