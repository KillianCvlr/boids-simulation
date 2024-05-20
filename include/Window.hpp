#pragma once
#include "RenderHandler.hpp"
#include "God.hpp"

#include <SDL.h>
#include <iostream>
#include <memory>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900

#define LINE_NUMBER 120
#define COLUMN_NUMBER 90

#define FPS 6

enum class WindowState {
    RUNNING,
    PAUSE,
    EXIT
};



class Window {
public:
    Window();
    ~Window();

    void mainLoop();

    WindowState handleEvents(SDL_Event event, WindowState const& windowState);

private:

    RenderHandler renderHandler_;
    WindowState windowState_;
};