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
#include "texture_manager.h"

GLuint display_width, display_height;
float half_width = 100.0f, half_height = 100.0f;

// The following variables are used to track movement and direction

// How high up is the head
float head_height = 0.0f;


// Vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = head_height;

// XZ position of the camera
float x = 0.0f, z = 1.0f;

// What angle are we pointing
float x_angle = sin(0.0f);
float z_angle = -cos(0.0f);
float y_angle = -sin(0.0f);

// Movement
float speed = 0.05f;

// Input
unsigned char keys[127] = {0};
float mouse_x_location = 0.0f, mouse_y_location = 0.0f;
bool after_reshape = true;
bool skip_mouse = false;

// The room
Room *room;

void draw_room(void)
{
    room->draw();
}

void compute_angle()
{
    // update camera's direction
    x_angle = sin(3.14159f / 2.0f * mouse_x_location);
    z_angle = -cos(3.14159f / 2.0f * mouse_x_location);
    y_angle = sin(3.14159f / 2.0f *  -mouse_y_location);
    
    // We can apply multipliers later if we want
    lx = x_angle;
    lz = z_angle;
    ly = y_angle;
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
    
    room->clip(x, z);
}

void reshape(int w, int h)
{
    // Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
    
	float ratio =  w * 1.0f / h;
    
    display_height = h;
    display_width = w;
    half_width = display_width / 2.0f;
    half_height = display_height / 2.0f;

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
    
    after_reshape = true;
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
	//printf("x: %.2f, head_height: %.2f, z: %.2f, lx: %.2f, ly: %.2f, lz: %.2f\n", x, head_height, z, lx, ly, lz);

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

void mouseFunc(int button, int state, int x, int y)
{

}

void move_cursor_to_center()
{
    // Warp back to center. But use non-glut methods on Apple
    // Glut has a .25 delay on Apple when you warp. This causes a stutter
    // This fix is recommended at
    // http://stackoverflow.com/questions/10196603/using-cgeventsourcesetlocaleventssuppressioninterval-instead-of-the-deprecated/17547015#17547015
#if __APPLE__
    CGPoint warpPoint = CGPointMake(half_width, half_height);
    CGWarpMouseCursorPosition(warpPoint);
    CGAssociateMouseAndMouseCursorPosition(true);
#else
    skip_mouse = true;
    glutWarpPointer((int)half_width, (int)half_height);
#endif
}

void mouseMove(int x, int y)
{
	if (skip_mouse == true) {
		skip_mouse = false;
		return;
	}
	// On windows this was getting called before reshape set the h,w
	// This caused a very weird bug
	if (half_height < 1.0f)
		half_height = 1.0f;
	if (half_width < 1.0f)
		half_width = 1.0f;
    
    if (after_reshape) {
        // Don't just move, since we didn't start off at center
        after_reshape = false;
        move_cursor_to_center();
        return;
    }

    mouse_x_location += (x - half_width) / half_width;
    mouse_y_location += (y - half_height) / half_height;
    

	if (mouse_y_location < -0.3f)
        mouse_y_location = -0.3f;
    if (mouse_y_location > 0.6f)
        mouse_y_location = 0.6f;
    if (mouse_x_location > 2.0f)
        mouse_x_location -= 4.0f;
    if (mouse_x_location < -2.0f)
        mouse_x_location += 4.0f;
    
    move_cursor_to_center();
}
 
void idle()
{
    display();
}

int main(int argc, char **argv)
{
  // init GLUT and create window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(800,100);
  glutInitWindowSize(640,640);
  glutCreateWindow("Unhinged");
  glutFullScreen();
  
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	//Disable color materials, so that glMaterial calls work
	glDisable(GL_COLOR_MATERIAL);
  
  TextureManager::Instance()->LoadTextures({
    "marble.jpg",
    "rust.jpg",
    "darkwood.jpg",
    "wall.jpg"
  });

  // Setup our display callbacks
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);

  // Handle keyboard down/up
  glutKeyboardFunc(pressKey);
  glutKeyboardUpFunc(releaseKey);
  glutIgnoreKeyRepeat(1);

  // Handle mouse events
  glutSetCursor(GLUT_CURSOR_NONE);
  glutPassiveMotionFunc(mouseMove);
  glutMouseFunc(mouseFunc);

  room = new Room();

  // enter GLUT event processing cycle
  glutMainLoop();

  return 0;
}

