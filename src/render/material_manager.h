//
//  material_manager.h
//  osx_unhinged
//
//  Created by Ben Lewis on 7/6/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__material_manager__
#define __osx_unhinged__material_manager__

#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#include "render/gl_headers.h"
#include "third_party/SOIL/SOIL.h"

class Material;

using namespace std;

class MaterialManager {
public:
	static MaterialManager* Instance();
	virtual ~MaterialManager();
  
	// Set the current material using standard OpenGL calls
	void BindMaterial(string name);
  
  // Just return the current material
  Material* get_material(string name) { return materials_[name]; }
  
protected:
	MaterialManager();
  
  // Our singleton instance
	static MaterialManager* instance_;
  
  // We'll use this to keep track of loaded materials
	std::map<string, Material*> materials_;

private:
  // Loads all materials into our vector
	void LoadMaterials();
  
};

#endif /* defined(__osx_unhinged__material_manager__) */
