#include "../include/Window.hpp"

#include "RenderHandler.hpp"
#include "God.hpp"

#include <iostream>
#include <memory>

Window::Window()
    : renderHandler_("crowd-simulation",SCREEN_X, SCREEN_Y ), windowState_(WindowState::PAUSED)
{
}

Window::~Window()
{
}

void Window::mainLoop()
{   

    std::cout << "Creating God" << std::endl;
    God god(SCREEN_X, SCREEN_Y, NB_CELLULAR_UNITS);
    std::cout << "God created" << std::endl;
    

    // Gestion des inputs
    SDL_Event e;
    windowState_ = WindowState::RUNNING;
    while ( windowState_ == WindowState::RUNNING )
    {   
        mainLoopRunning :
        windowState_ = handleEvents(e, &god);
        god.updateUniverse();
        renderHandler_.renderUniverse(&god);
        SDL_Delay(1000 / FPS);
    }

    switch (windowState_)
    {
    case WindowState::EXIT:
        break;
    
    case WindowState::PAUSED:
        std::cout << "Universe paused" << std::endl;
        while (windowState_ == WindowState::PAUSED)
        {
            windowState_ = handleEvents(e, &god);
        }
        if (windowState_ == WindowState::RUNNING)
        {
            goto mainLoopRunning;
        }
        break;
        
    default:
        break;
    }
    std::cout << "Main loop finished" << std::endl;
    return;
}

WindowState Window::handleEvents(SDL_Event e, God *god)
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            return WindowState::EXIT;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_SPACE:
                return (windowState_ == WindowState::PAUSED ? WindowState::RUNNING : WindowState::PAUSED);
                break;

            case SDLK_ESCAPE:
                return WindowState::EXIT;
                break;
            
            case SDLK_n:
                god->newUniverse(NB_CELLULAR_UNITS);
                break;
            
            case SDLK_r:
                god->destroyUniverse();
                std::cout << "THANOS ALL" << std::endl;
                break;

            case SDLK_q:
                renderHandler_.switchRenderQuadTree();
                renderHandler_.renderUniverse(god);
                break;
            
            case SDLK_f:
                renderHandler_.switchRenderFieldViews();
                renderHandler_.renderUniverse(god);
                break;
                
            case SDLK_c:
                renderHandler_.switchRenderCells();
                renderHandler_.renderUniverse(god);
                break;

            case SDLK_p:
                renderHandler_.switchRenderProximity();
                renderHandler_.renderUniverse(god);
                break;

            case SDLK_l:
                renderHandler_.switchRenderNeighboringLinks();
                renderHandler_.renderUniverse(god);
                break;
            
            case SDLK_a:
                renderHandler_.switchRenderFirst();
                renderHandler_.renderUniverse(god);
                break;
                
            default:
                break;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            god->addCell(x, y);
            renderHandler_.renderUniverse(god);
        }
    }
    return windowState_;
}
