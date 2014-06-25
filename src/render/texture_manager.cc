//
//  texture_manager.cc
//  osx_unhinged
//
//  Created by Ben Lewis on 6/23/14.
//  Copyright (c) 2014 ben. All rights reserved.
//

#include "render/texture_manager.h"

TextureManager* TextureManager::instance_(0);

TextureManager* TextureManager::Instance() {
	if(!instance_)
		instance_ = new TextureManager();
    
	return instance_;
}

TextureManager::TextureManager() {

}


TextureManager::~TextureManager() {
	instance_ = 0;
}

void TextureManager::LoadTextures(vector<string> filenames) {
  for (vector<string>::iterator i = filenames.begin(); i != filenames.end(); ++i) {
    LoadTexture(*i);
  }
}

void TextureManager::LoadTexture(string filename) {
  // OpenGL will use assignment to set this
  GLuint texture_id = -1;

  // Create a texture for the floor
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  int width, height;
  string file = ASSET_PATH + "textures/" + filename;
  unsigned char* image = SOIL_load_image(file.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                    GL_RGB, GL_UNSIGNED_BYTE, image );
  SOIL_free_image_data(image);


  textures_[filename] = texture_id;
}


void TextureManager::BindTexture(string filename) {
  assert(textures_.find(filename) != textures_.end());
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, textures_[filename]);
}
