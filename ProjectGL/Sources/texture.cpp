//
//  texture.cpp
//  TestGL
//
//  Created by Radoka on 3/14/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#include "texture.hpp"
#include <iostream>
#include "stb_image.h"
#include <cassert>
#include <string>

Texture::Texture(const std::string& fileName)
{
    int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
    
    if(data == NULL)
        std::cerr << "Unable to load texture: " << fileName << std::endl;
    
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

