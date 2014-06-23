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

enum direction {
	SPIN_CLOCKWISE,
	SPIN_COUNTERCLOCKWISE,
	SPIN_NONE
};

class Gear : public Piece
{
public:
	Gear(int x, int y, int z, Room *gr, direction _spin_direction, float _angle) :
		Piece(x, y, z, gr), spin_direction(_spin_direction), angle(_angle)  {
		create_list(); 
	}
	void update(int ticks);
	void draw();

private:
    void create_list();
	float angle = 0.0f;
	direction spin_direction;

};
#endif /* defined(__osx_unhinged__gear__) */
