//
//  display.hpp
//  TestGL
//
//  Created by Radoka on 3/12/18.
//  Copyright © 2018 radoslav.genov.1992. All rights reserved.
//

#ifndef display_hpp
#define display_hpp

#include <string>
#include <SDL2/SDL.h>

class Display {
    
public:
    Display(int width, int height, const std::string& title);
    virtual ~Display();
    
    void Clear(float r, float g, float b, float a);
    void Update();
    bool IsClosed();
    
private:
    Display(const Display& other) {}
    void operator=(const Display& other) {}
    
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    
    bool m_isClosed;
};

#endif /* display_hpp */
