//
//  shader.hpp
//  TestGL
//
//  Created by Radoka on 3/12/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include "shader.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include <GL/glew.h>
#include <iostream>
#include <string>

class Shader {
    
public:
    Shader(const std::string& filename);
    virtual ~Shader();
    
    void Bind();
    void Update(const Transform &transform, const Camera &camera);
    
private:
    Shader(const Shader &other) {}
    void operator=(const Shader& other) {}
  
    static const unsigned int NUM_UNIFORMS = 3;
    static const unsigned int NUM_SHADERS = 2;
    
    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};


#endif /* shader_hpp */
