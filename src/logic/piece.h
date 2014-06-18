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


#ifndef __osx_unhinged__piece__
#define __osx_unhinged__piece__

#include "gl_headers.h"

class piece
{
public:
    void draw();
    void update(int ticks);
    void clip(float x_old, float y_old, float &x_new, float &y_new);
    
private:
    int x, y, z; //the lower back left of the piece
    
};

#endif /* defined(__osx_unhinged__piece__) */
