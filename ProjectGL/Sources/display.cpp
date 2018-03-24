//
//  display.cpp
//  TestGL
//
//  Created by Radoka on 3/12/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#include "display.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title) {
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    this->m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    
    m_glContext = SDL_GL_CreateContext(this->m_window);
    
    glewExperimental = GL_TRUE;
    GLenum status = glewInit();

    
    if(status != GLEW_OK){
        std::cerr << "GLEW failed to initialize!" << std::endl;
    }

    this->m_isClosed = false;
    
//    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Display::~Display(){
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a){
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed(){
    return this->m_isClosed;
}

void Display::Update(){
    SDL_GL_SwapWindow(m_window);
    SDL_Event e;
    
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            m_isClosed = true;
        }
    }
}
