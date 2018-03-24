//
//  main.cpp
//  TestGL
//
//  Created by Radoka on 3/12/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#include <iostream>
#include "display.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "transform.hpp"
#include "texture.hpp"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
//#include <AL/al.h>
//#include <AL/alc.h>

#define WIDTH 1300
#define HEIGHT 800

int main(int argc, const char** argv) {
    
    
    Display display(WIDTH, HEIGHT, "Hello World");
  
    Mesh mesh3("/Users/radoka/Desktop/cos310-computer-graphics/code/ProjectGL/ProjectGL/res/dragon.obj");

    Shader shader("/Users/radoka/Desktop/cos310-computer-graphics/code/ProjectGL/ProjectGL/res/basicShader");
    
    Texture texture("/Users/radoka/Desktop/cos310-computer-graphics/code/ProjectGL/ProjectGL/res/texture.jpeg");
    
    Camera camera(glm::vec3(0.0f, 0.0f, -7.0f), 70.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    
    Transform transform;
    
    float counter = 0.0f;
    float counter2 = 0.0f;
    
    glm::vec3 scale = glm::vec3(0.3f, 0.3f, 0.3f);
    
    while (!display.IsClosed()) {
        display.Clear(0.0f, 0.0f, 0.0f, 1.0f);
        transform.GetRot()->y = counter * 5;
        transform.GetRot()->z = counter * 5;
        transform.GetRot()->z = sinf(counter2);
        transform.SetScale(scale);
        shader.Bind();
        texture.Bind();
        shader.Update(transform, camera);
        mesh3.Draw();
        display.Update();
        counter += 0.01f;
        counter2 += 0.2;
    }
    
    return 0;
}






