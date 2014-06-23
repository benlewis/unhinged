//
//  room.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "room.h"
#include "gear.h"
#include "SOIL/SOIL.h"

Room::Room()
{
    // Room stuff
    // TODO: Move to the room file
    left_wall = -2.0f;
    right_wall = 2.0f;
    room_ceiling = 1.0f;
    room_floor = -1.0f;
    front_wall = 2.0f;
    back_wall = -2.0f;
    clipping_plane = 0.15f;
    
    // Create a texture for the floor
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int width, height;
    string file = ASSET_PATH + "textures/wall.jpg";
    unsigned char* image = SOIL_load_image(file.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
	//glGenerateMipmap(GL_TEXTURE_2D);
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                      GL_RGB, GL_UNSIGNED_BYTE, image );
    SOIL_free_image_data(image);
    
    
	pieces.push_back(new Gear(10, 5, 5, this, SPIN_CLOCKWISE, 0.0f));
	pieces.push_back(new Gear(11, 5, 5, this, SPIN_COUNTERCLOCKWISE, -8.0f));
	pieces.push_back(new Gear(12, 5, 5, this, SPIN_CLOCKWISE, 0.0f));
}

void Room::draw()
{
    glPushMatrix();

    /* Floor */
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(left_wall,room_floor,front_wall);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(right_wall,room_floor,front_wall);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(right_wall,room_floor,back_wall);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(left_wall,room_floor,back_wall);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glShadeModel(GL_SMOOTH);

    /* Ceiling */
    glColor3f(0.55f,0.55f,0.55f);
    glVertex3f(left_wall,room_ceiling,back_wall);
    glVertex3f(right_wall,room_ceiling,back_wall);
    glVertex3f(right_wall,room_ceiling,front_wall);
    glVertex3f(left_wall,room_ceiling,front_wall);
    /* Walls */
    glColor3f(0.35f,0.35f,0.35f);
    glVertex3f(left_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_ceiling,front_wall);
    glVertex3f(left_wall,room_ceiling,front_wall);
    
    glVertex3f(left_wall,room_floor,back_wall);
    glVertex3f(right_wall,room_floor,back_wall);
    glVertex3f(right_wall,room_ceiling,back_wall);
    glVertex3f(left_wall,room_ceiling,back_wall);
    
    glColor3f(0.75f,0.75f,0.75f);
    glVertex3f(right_wall,room_ceiling,front_wall);
    glVertex3f(right_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,back_wall);
    glVertex3f(right_wall,room_ceiling,back_wall);
    
    glVertex3f(left_wall,room_ceiling,front_wall);
    glVertex3f(left_wall,room_floor,front_wall);
    glVertex3f(left_wall,room_floor,back_wall);
    glVertex3f(left_wall,room_ceiling,back_wall);
    glEnd();
    
    glPopMatrix();

	vector<Piece*>::iterator it;
	for (it = pieces.begin(); it != pieces.end(); ++it) {
		Piece *piece = *it;
		glColor3f(0.75f, 0.1f, 0.0f);
		piece->update(0);
		piece->draw();
	}

    
}

float Room::get_width()
{
    return right_wall - left_wall;
}

float Room::get_length()
{
    return front_wall - back_wall;
}

float Room::get_height()
{
    return room_ceiling - room_floor;
}

float Room::get_board_width()
{
	return board_width;
}

float Room::get_board_length()
{
	return board_length;
}

float Room::get_board_height()
{
	return board_height;
}

void Room::clip(float &x, float &z)
{
    if (x < left_wall + clipping_plane)
        x = left_wall + clipping_plane;
    if (x > right_wall - clipping_plane)
        x = right_wall - clipping_plane;
    if (z > front_wall - clipping_plane)
        z = front_wall - clipping_plane;
    if (z < back_wall + clipping_plane)
        z = back_wall + clipping_plane;
}
