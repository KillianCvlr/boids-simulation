#pragma once
#include "RenderHandler.hpp"
#include "God.hpp"

#include <SDL.h>
#include <iostream>
#include <memory>

#define SCREEN_X 2000
#define SCREEN_Y 1000


#define COLUMN_NUMBER (SCREEN_X / CELL_SIZE)
#define LINE_NUMBER (SCREEN_Y / CELL_SIZE)

#define FPS 900

#define NB_CELLULAR_UNITS ((COLUMN_NUMBER * LINE_NUMBER) / 90)

enum class WindowState {
    RUNNING,
    PAUSED,
    EXIT
};



class Window {
public:
    Window();
    ~Window();

    void mainLoop();

    WindowState handleEvents(SDL_Event event, God &god);

private:

    RenderHandler renderHandler_;
    WindowState windowState_;
};