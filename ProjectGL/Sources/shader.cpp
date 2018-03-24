//
//  shader.cpp
//  TestGL
//
//  Created by Radoka on 3/12/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#include "shader.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>


static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string errorMessage);
static std::string LoadShader(const std::string& filename);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& filename){
    m_program = glCreateProgram();
    m_shaders[0] = CreateShader(LoadShader(filename + ".glslv"), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(filename + ".glslf"), GL_FRAGMENT_SHADER);

    for (unsigned i = 0; i < NUM_SHADERS; i++) {
        glAttachShader(m_program, m_shaders[i]);
    }
    
    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texCoord");
    glBindAttribLocation(m_program, 2, "normal");
    
    
    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program Linking Failed: ");
    
    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is Invalid: ");
    
    m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
    m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
    m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
}

Shader::~Shader(){
    for (unsigned i = 0; i < NUM_SHADERS; i++) {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }
    glDeleteProgram(m_program);
}

void Shader::Bind(){
    glUseProgram(m_program);
}

void Shader::Update(const Transform &transform, const Camera &camera){
    glm::mat4 MVP = transform.GetMVP(camera);
    glm::mat4 Normal = transform.GetModel();
    
    glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
    glUniform3f(m_uniforms[2], 0.0f, -7.0f, 0.0f);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType){
    GLuint shader = glCreateShader(shaderType);
    
    if (shader == 0)
        std::cerr << "Error: Shader creation failed" << std::endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];
    
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = (int)text.length();
    
    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    glCompileShader(shader);
    
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");
    
    return shader;
}

static std::string LoadShader(const std::string& filename){
    std::ifstream file;
    file.open(filename.c_str());
    
    std::string output;
    std::string line;
    
    if (file.is_open()){
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader: " + filename << std::endl;
    }
    return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string errorMessage){
    GLint success = 0;
    GLchar error[1024] = { 0 };
    
    if (isProgram) {
        glGetProgramiv(shader, flag, &success);
    } else {
        glGetShaderiv(shader, flag, &success);
    }
    
    if (success == GL_FALSE) {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        std::cerr << errorMessage << ": " << error << std::endl;
    }
    
}




