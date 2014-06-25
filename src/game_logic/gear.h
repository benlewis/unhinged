//
//  gear.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__gear__
#define __osx_unhinged__gear__

#include "game_logic/piece.h"

enum Direction {
	SPIN_CLOCKWISE,
	SPIN_COUNTERCLOCKWISE,
	SPIN_NONE
};

class Gear : public Piece {
public:
	Gear(int x, int y, int z, Room *room, Direction spin_direction, GLfloat angle) :
		Piece(x, y, z, room), spin_direction_(spin_direction), angle_(angle)  {
		create_list(); 
	}
	void update(int ticks);
	void draw();

private:
  void create_list();
	GLfloat angle_ = 0.0f;
	Direction spin_direction_;

};

#endif /* defined(__osx_unhinged__gear__) */
