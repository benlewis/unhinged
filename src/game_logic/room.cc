//
//  room.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/15/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "game_logic/room.h"
#include "game_logic/face.h"

#include "render/material_manager.h"

#include <stdlib.h>
#include <stack>

Room::Room() {

  //CreateRoomWalls();
  CreateBox(glm::vec3(0.0f, 0.0f, -0.75f), 5, 2, 2);
  //CreateBox(glm::vec3(1.0f, 0.0f, -0.75f), 1, 2, 2);
}

void Room::CreateBox(glm::vec3 box_center, GLint w, GLint h, GLint l) {
  Material *material = MaterialManager::Instance()->get_material("cyan_plastic");
    glm::vec3 location = box_center;
    location.z += l * facet_size_ / 2.0f;
  glm::vec4 rotation = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
  Face *front = new Face(this, material, "", w, h, location, rotation, PLANE_XY, true);
  faces_.push_back(front);

    location.z -= l * facet_size_;
  rotation = glm::vec4(0.0f, 1.0f, 0.0f, 180.0f);
  Face *back = new Face(this, material, "", w, h, location, rotation, PLANE_XY, true);
  faces_.push_back(back);
  
    location = box_center;
    location.x -= w * facet_size_ / 2.0f;
    rotation = glm::vec4(0.0f, 1.0f, 0.0f, -90.0f);
  Face *left = new Face(this, material, "", l, h, location, rotation, PLANE_YZ, true);
  faces_.push_back(left);
    
    location.x += w * facet_size_;
    rotation = glm::vec4(0.0f, 1.0f, 0.0f, 90.0f);
  Face *right = new Face(this, material, "", l, h, location, rotation, PLANE_YZ, true);
  faces_.push_back(right);
    
    location = box_center;
    location.y += h * facet_size_ / 2.0f;
    rotation = glm::vec4(1.0f, 0.0f, 0.0f, -90.0f);
  Face *top = new Face(this, material, "", w, l, location, rotation, PLANE_XZ, true);
  faces_.push_back(top);
    
    location.y -= h * facet_size_;
    rotation = glm::vec4(1.0f, 0.0f, 0.0f, +90.0f);
  Face *bottom = new Face(this, material, "", w, l, location, rotation, PLANE_XZ, true);
  faces_.push_back(bottom);
}

void Room::CreateRoomWalls() {
  glm::vec3 location = glm::vec3(width_ / -2.0f, height_ / -2.0f, length_ / -2.0f);
  glm::vec4 rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f); // no rotation for our back wall
  Face *back_wall = new Face(this, nullptr, "darkwood.jpg", width_ / facet_size_, height_ / facet_size_, location, rotation, PLANE_XY, false);
  faces_.push_back(back_wall);
  
  location = glm::vec3(width_ / 2.0f, height_ / -2.0f, length_ / 2.0f);
  rotation = glm::vec4(0.0f, 1.0f, 0.0f, 180.0f);
  Face *front_wall = new Face(this, nullptr, "darkwood.jpg", width_ / facet_size_, height_ / facet_size_, location, rotation, PLANE_XY, false);
  faces_.push_back(front_wall);

  location = glm::vec3(width_ / -2.0f, height_ / -2.0f, length_ / 2.0f);
  rotation = glm::vec4(1.0f, 0.0f, 0.0f, -90.0f);
  Face *floor = new Face(this, nullptr, "darkwood.jpg", width_ / facet_size_, length_ / facet_size_, location, rotation, PLANE_XZ, false);
  faces_.push_back(floor);

  location = glm::vec3(width_ / -2.0f, height_ / 2.0f, length_ / -2.0f);
  rotation = glm::vec4(1.0f, 0.0f, 0.0f, 90.0f);
  Face *ceiling = new Face(this, nullptr, "darkwood.jpg", width_ / facet_size_, length_ / facet_size_, location, rotation, PLANE_XZ, false);
  faces_.push_back(ceiling);
  
  location = glm::vec3(width_ / -2.0f, height_ / -2.0f, length_ / 2.0f);
  rotation = glm::vec4(0.0f, 1.0f, 0.0f, 90.0f);
  Face *left_wall = new Face(this, nullptr, "darkwood.jpg", width_ / facet_size_, height_ / facet_size_, location, rotation, PLANE_YZ, false);
  faces_.push_back(left_wall);
  
  location = glm::vec3(width_ / 2.0f, height_ / -2.0f, length_ / -2.0f);
  rotation = glm::vec4(0.0f, 1.0f, 0.0f, -90.0f);
  Face *right_wall = new Face(this, nullptr, "darkwood.jpg", width_ / facet_size_, height_ / facet_size_, location, rotation, PLANE_YZ, false);
  faces_.push_back(right_wall);
}

void Room::Draw() {
  GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  
  GLfloat lightColor[] = {0.3f, 0.3f, 0.3f, 1.0f};
  GLfloat lightPos[] = {0.0f, 0.0f, -2.0f, 1.0f};
  GLfloat backPos[] = {0.0f, 0.0f, 2.0f, 1.0f};
  GLfloat backDir[] = {0.0f, 0.0f, -1.0f, 1.0f};

  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos);

  glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor);
  glLightfv(GL_LIGHT2, GL_SPECULAR, lightColor);
  glLightfv(GL_LIGHT2, GL_POSITION, backPos);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, backDir);
  
  for (vector<Face*>::iterator i = faces_.begin(); i != faces_.end(); i++) {
    glPushMatrix();
    Face *face = *i;
    face->Draw();
    glPopMatrix();
  }
}

bool Room::AddGear(Gear *gear) {
  // Set all next rotations to their base state
  for (vector<Gear*>::iterator i = gears_.begin(); i != gears_.end(); i++) {
    Gear *g = *i;
    g->ClearNextRotation();
  }
  
  stack<Gear *> spinning_gears;

  // Add all spinning gears to the stack
  for (vector<Gear*>::iterator i = gears_.begin(); i != gears_.end(); i++) {
    Gear *g = *i;
    if (g->get_next_rotation() != SPIN_NONE) {
      spinning_gears.push(g);
    }
  }

  while (!spinning_gears.empty()) {
    Gear *spinning_gear = spinning_gears.top();
    spinning_gears.pop();
    
    // Check other gears to see if we should spin them
    for (vector<Gear*>::iterator i = gears_.begin(); i != gears_.end(); i++) {
      Gear *g = *i;
      if (g != spinning_gear && spinning_gear->Intersects(g)) { // don't check ourself
        if (g->get_next_rotation() == SPIN_NONE) {
          // We need to check this guy next
          spinning_gears.push(g);
        }
        if (!g->SetNextRotation(spinning_gear->OppositeRotation())) {
          // This means that the rotation is in two directions - not allowed
          return false;
        }
        
      }
    }
  }
  
  // Enable all new rotations
  for (vector<Gear*>::iterator i = gears_.begin(); i != gears_.end(); i++) {
    Gear *g = *i;
    g->EnableNextRotation();
  }
  
  return true;
}

void Room::Clip(glm::vec3 old_location, glm::vec3 &new_location) {
  for (vector<Face*>::iterator i = faces_.begin(); i != faces_.end(); i++) {
    Face *face = *i;
    face->Clip(old_location, new_location);
  }
}
