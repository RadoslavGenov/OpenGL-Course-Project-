//
//  texture.hpp
//  TestGL
//
//  Created by Radoka on 3/14/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <GL/glew.h>
#include <string>

class Texture {
    
public:
    Texture(const std::string& fileName);
    virtual ~Texture();
    
    void Bind();
private:
    Texture(const Texture& other) {}
    void operator=(const Texture& other) {}
    
    GLuint m_texture;
};

#endif /* texture_hpp */
