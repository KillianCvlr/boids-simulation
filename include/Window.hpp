#pragma once
#include "RenderHandler.hpp"

#include <SDL.h>
#include <iostream>
#include <memory>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 900
#define FPS 60

enum class WindowState {
    RUNNING,
    PAUSE
};



class Window {
public:
    Window();
    ~Window();

    void mainLoop();

private:

    RenderHandler m_renderHandler;
    WindowState m_WindowState;
};