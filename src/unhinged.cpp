//
//  unhinged.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "gl_headers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "room.h"

GLuint display_width, display_height;

// The following variables are used to track movement and direction

// How high up is the head
float head_height = 0.0f;


// Vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = head_height;

// XZ position of the camera
float x = 0.0f, z = 1.0f;

// What angle are we pointing
float x_angle = sin(0);
float z_angle = -cos(0);
float y_angle = -sin(0);

// Movement
float speed = 0.05f;

// Input
unsigned char keys[127] = {0};
float mouse_x_location = 0.0f, mouse_y_location = 0.0f;
float mouse_extra_x = 0.0f, mouse_extra_speed = 0.02f;

// The room
room *game_room;

void draw_room(void)
{
    game_room->draw();
}

void compute_angle()
{
    if (mouse_extra_x > 0)
        mouse_extra_x += mouse_extra_speed;
    else if (mouse_extra_x < 0)
        mouse_extra_x -= mouse_extra_speed;
    
    // update camera's direction
    x_angle = sin(mouse_x_location + mouse_extra_x);
    z_angle = -cos(mouse_x_location + mouse_extra_x);
    y_angle = sin(-mouse_y_location);
    
    lx = x_angle * (game_room->get_width());
    lz = z_angle * (game_room->get_length());
    ly = y_angle * (game_room->get_height());
}

void compute_pos()
{
    float delta_move = 0.0f;
    if (keys['w'] == 1)
        delta_move += 1.0;
    if (keys['s'] == 1)
        delta_move -= 1.0;

    float delta_side = 0.0f;
    if (keys['d']  == 1)
        delta_side += 1.0;
    if (keys['a'] == 1)
        delta_side -= 1.0;
    
	x += delta_move * x_angle * speed - delta_side * z_angle * speed;;
	z += delta_move * z_angle * speed + delta_side * x_angle * speed;
    
    game_room->clip(x, z);
}

void reshape(int w, int h)
{
    // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
    
	float ratio =  w * 1.0 / h;
    
    display_height = h;
    display_width = w;
    
    // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
    
    // Reset Matrix
	glLoadIdentity();
    
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
    
	// Set the correct perspective.
	gluPerspective(65.0f, ratio, 0.1f, 10.0f);
    
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    // Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Reset transformations
	glLoadIdentity();
    
    // Move and position if necessary
    compute_angle();
    compute_pos();

	// Set the camera
	gluLookAt(
              x,      head_height,   z,
              x+lx,   ly,   z+lz,
              0.0f,   1.0f,   0.0f
              );
    
    draw_room();
    
    glutSwapBuffers();
}

void releaseKey(unsigned char key, int x, int y)
{
    keys[tolower(key)] = 0;
}

void pressKey(unsigned char key, int xx, int yy)
{
    if (key == 27) {
        exit(0);
    }
    
	keys[tolower(key)] = 1;
}

void mouseMove(int x, int y)
{
    if (x > display_width - 5)
        mouse_extra_x += mouse_extra_speed;
    else if (x < 5)
        mouse_extra_x -= mouse_extra_speed;
    else
        mouse_extra_x = 0.0f;
    
    
    float half_width = display_width / 2.0;
    float half_height = display_height / 2.0;
    mouse_x_location = (x - half_width) / half_width;
    mouse_y_location = (y - half_height) / half_height;
}

int main(int argc, char **argv)
{
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,640);
    glutCreateWindow("Unhinged");
    glutFullScreen();
    glEnable(GL_DEPTH_TEST);
    
    // Setup our display callbacks
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
    
    // Handle keyboard down/up
	glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);
    glutIgnoreKeyRepeat(1);
    
    // Handle mouse events
    glutPassiveMotionFunc(mouseMove);
    
    game_room = new room();
    
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 0;
}

