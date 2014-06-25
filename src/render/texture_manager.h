//
//  texture_manager.h
//  osx_unhinged
//
//  Created by Ben Lewis on 6/23/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#ifndef __osx_unhinged__texture_manager__
#define __osx_unhinged__texture_manager__

#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#include "render/gl_headers.h"
#include "third_party/SOIL/SOIL.h"


using namespace std;

class TextureManager {
public:
	static TextureManager* Instance();
	virtual ~TextureManager();
    
  // Loads a texture into our vector
	void LoadTexture(string filename);
    
  // A helper method to load multiple textures at once
  void LoadTextures(vector<string> filenames);
    
	// Set the current texture using standard OpenGL calls
  // The caller is responsible for glEnable/glDisable
	void BindTexture(string filename);
    
    
protected:
	TextureManager();
    
  // Our singleton instance
	static TextureManager* instance_;
    
  // We'll use this to keep track of loaded textures
	std::map<string, GLuint> textures_;
    
};

#endif /* defined(__osx_unhinged__texture_manager__) */
