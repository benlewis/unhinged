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
float mouse_x_location = 0.0f;
float mouse_y_location = 0.0;

// Room stuff
// TODO: Move to the room file
float left_wall = -1.0f, right_wall = 1.0f;
float room_ceiling = 1.0f, room_floor = -1.0f;
float front_wall = 2.0f, back_wall = -2.0f;
float clipping_plane = 0.15f;

void draw_room(void)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glShadeModel(GL_SMOOTH);
    /* Floor */
    glColor3f(1.0,1.0,1.0);
    glVertex3f(left_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,back_wall);
    glVertex3f(left_wall,room_floor,back_wall);
    /* Ceiling */
    glColor3f(0.55,0.55,0.55);
    glVertex3f(left_wall,room_ceiling,back_wall);
    glVertex3f(right_wall,room_ceiling,back_wall);
    glVertex3f(right_wall,room_ceiling,front_wall);
    glVertex3f(left_wall,room_ceiling,front_wall);
    /* Walls */
    glColor3f(0.35,0.35,0.35);
    glVertex3f(left_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_floor,front_wall);
    glVertex3f(right_wall,room_ceiling,front_wall);
    glVertex3f(left_wall,room_ceiling,front_wall);
    
    glVertex3f(left_wall,room_floor,back_wall);
    glVertex3f(right_wall,room_floor,back_wall);
    glVertex3f(right_wall,room_ceiling,back_wall);
    glVertex3f(left_wall,room_ceiling,back_wall);
    
    glColor3f(0.75,0.75,0.75);
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
}

void clip()
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

void compute_angle()
{
    // update camera's direction
    x_angle = sin(mouse_x_location);
    z_angle = -cos(mouse_x_location);
    y_angle = sin(-mouse_y_location);
    
    lx = x_angle * (right_wall - left_wall);
    lz = z_angle * (front_wall - back_wall);
    ly = y_angle * (room_ceiling - room_floor);
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
    
    clip();
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
    
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 0;
}

