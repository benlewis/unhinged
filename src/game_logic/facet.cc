//
//  facet.cpp
//  osx_unhinged
//
//  Created by Ben Lewis on 6/24/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "game_logic/facet.h"

bool Facet::AddGear(Gear* gear) {
  if (HasGear()) {
    return false;
  } else {
    this->gear_ = gear;
    return true;
  }
}

void Facet::RemoveGear(Gear* gear) {
  this->gear_ = nullptr;
}

bool Facet::HasGear() {
  return (gear_ != nullptr);
}