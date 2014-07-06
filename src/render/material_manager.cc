//
//  material_manager.cc
//  osx_unhinged
//
//  Created by Ben Lewis on 7/6/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "render/material_manager.h"
#include "render/material.h"

#if defined _WIN32 || defined _WIN64
#include <assert.h>
#endif

MaterialManager* MaterialManager::instance_(0);

MaterialManager* MaterialManager::Instance() {
	if(!instance_)
		instance_ = new MaterialManager();
  
	return instance_;
}

MaterialManager::MaterialManager() {
  LoadMaterials();
}


MaterialManager::~MaterialManager() {
	instance_ = 0;
}

void MaterialManager::LoadMaterials() {
  // TODO: Read these from a file
  
  //
  //
  // A big thanks to http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
  // For providing these materials
  //
  //
  
  materials_["gold"] = new Material(0.24725f, 0.1995f, 0.0745f, 1.0f,
                                    0.75164f, 0.60648f, 0.22648f, 1.0f,
                                    0.628281f, 0.555802f, 0.366065f, 1.0f,
                                    51.2f);
  
  materials_["bronze"] = new Material(0.329412f, 0.223529f, 0.027451f, 1.0f,
                                      0.780392f, 0.568627f, 0.113725f, 1.0f,
                                      0.992157f, 0.941176f, 0.807843f, 1.0f,
                                      27.8974f);
  
  materials_["cyan_plastic"] = new Material(0.0f, 0.1f, 0.06f, 1.0f,
                                            0.0f, 0.50980392f, 0.50980392f, 1.0f,
                                            0.50196078f, 0.50196078f, 0.50196078f, 1.0f,
                                            32.0f);
  
  materials_["obsidian"] = new Material(0.05375f, 0.05f, 0.06625f, 0.82f,
                                        0.18275f, 0.17f, 0.22525f, 0.82f,
                                        0.332741f, 0.328634f, 0.346435f, 0.82f,
                                        38.4f);
}

void MaterialManager::BindMaterial(string name) {
  assert(materials_.find(name) != materials_.end());
  materials_[name]->EnableMaterial();
}

