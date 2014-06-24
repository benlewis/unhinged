//
//  piece.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//



#include "piece.h"

Piece::Piece(int x, int y, int z, Room *gr)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->draw_x = (float)x / gr->get_board_width() * gr->get_width() - gr->get_width() / 2.0f;
	this->draw_y = (float)y / gr->get_board_height() * gr->get_height() - gr->get_height() / 2.0f;
	this->draw_z = (float)z / gr->get_board_length() * gr->get_length() - gr->get_length() / 2.0f;

}

void Piece::draw()
{
	glPushMatrix();
	glTranslatef(draw_x, draw_y, draw_z);
	glCallList(list);
	glPopMatrix();
}

void Piece::update(int ticks)
{
	printf("base update\n");
}

void Piece::clip(float x_old, float y_old, float &x_new, float &y_new)
{
    // Pieces don't clip by default
    return;
}
