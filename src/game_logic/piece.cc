//
//  piece.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/17/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "game_logic/piece.h"
#include "game_logic/room.h"


Piece::Piece(int x, int y, int z, Room *room): x_(x), y_(y), z_(z) {
	this->draw_x_ = (GLfloat)x / room->get_board_width() * room->get_width() - room->get_width() / 2.0f;
	this->draw_y_ = (GLfloat)y / room->get_board_height() * room->get_height() - room->get_height() / 2.0f;
	this->draw_z_ = (GLfloat)z / room->get_board_length() * room->get_length() - room->get_length() / 2.0f;
}

void Piece::draw() {
	glPushMatrix();
	glTranslatef(draw_x_, draw_y_, draw_z_);
	glCallList(list_);
	glPopMatrix();
}

void Piece::update(int ticks) {
	printf("base update\n");
}

void Piece::clip(GLfloat x_old, GLfloat y_old, GLfloat &x_new, GLfloat &y_new) {
    // Pieces don't clip by default
    return;
}
