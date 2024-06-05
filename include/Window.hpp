#pragma once

#include "RenderHandler.hpp"
#include "God.hpp"

#include <iostream>
#include <memory>

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