#include "../include/Window.hpp"


Window::Window()
    : renderHandler_("breakout",SCREEN_X, SCREEN_Y ), windowState_(WindowState::PAUSE)
{
}

Window::~Window()
{
}

void Window::mainLoop()
{   

    std::cout << "Creating God" << std::endl;
    God god(COLUMN_NUMBER, LINE_NUMBER, 10);
    std::cout << "God created" << std::endl;
    

    // Gestion des inputs
    SDL_Event e;
    windowState_ = WindowState::RUNNING;
    while ( god.updateUniverse(e) == UniverseState::ALIVE )
    {   
        mainLoopRunning :
        renderHandler_.renderUniverse(god);
        SDL_Delay(1000 / FPS);
    }

    switch (god.getUniverseState())
    {
    case UniverseState::DEAD:
        break;
    
    case UniverseState::PAUSED:
        std::cout << "Universe paused" << std::endl;
        windowState_ = WindowState::PAUSE;
        UniverseState universeState;
        while (windowState_ == WindowState::PAUSE)
        {
            universeState = god.handleMe(e);
            if(universeState == UniverseState::ALIVE)
            {
                windowState_ = WindowState::RUNNING;
                goto mainLoopRunning;
            }
            else if (universeState == UniverseState::DEAD)
            {
                windowState_ = WindowState::EXIT;
                break;
            }
        }
        break;
        
    default:
        break;
    }
    std::cout << "Main loop finished" << std::endl;
    return;
}
