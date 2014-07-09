//
//  facet.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/24/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "game_logic/room.h"
#include "game_logic/facet.h"
#include "game_logic/face.h"
#include "game_logic/gear.h"

#include "render/material.h"

bool Facet::AddGear(Gear* gear) {
  if (HasGear()) {
    return false;
  } else {
    if (room_->AddGear(gear)) {
      this->gear_ = gear;
      return true;
    } else {
      return false;
    }
    
  }
}

void Facet::RemoveGear(Gear* gear) {
  this->gear_ = nullptr;
}

bool Facet::HasGear() {
  return (gear_ != nullptr);
}

Plane Facet::get_plane() {
  return face_->get_plane();
}

void Facet::Draw() {
  if (HasPeg()) {
    glPushMatrix();
    peg_material_->EnableMaterial();
    GLfloat dw = room_->get_facet_size();
    GLfloat dh = dw;
    
    GLfloat radius = dw / 5.0f;
    
    glTranslatef(dw / 2.0f, dh / 2.0f, 0.0f);
    
    glTranslatef(0.0f, 0.0f, 0.025f);
    glutSolidSphere(radius, 16, 16);
    if (HasGear()) {
      // Make the gear a bit offset from the facet edge
      glTranslatef(0.0f, 0.0f, 0.006f);
      gear_->Update(0);
      gear_->Draw();
    }
    glPopMatrix();
  }
}