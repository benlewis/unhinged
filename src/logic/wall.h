//
//  wall.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/22/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__wall__
#define __osx_unhinged__wall__

enum Face {
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    CEILING,
    FLOOR
};

class Wall
{
public:
    Wall(Face face): face_(face) {};
    
private:
    Face face_;
};

#endif /* defined(__osx_unhinged__wall__) */
