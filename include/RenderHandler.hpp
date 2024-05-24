#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>

#include "God.hpp" 
#include <cmath>

#include "SDLColors.hpp"


class RenderHandler {
public:
    RenderHandler(char const *title, int const width, int const height);
    ~RenderHandler();

    void renderUniverse(God const& god);
    void renderCells(God const& god);

    void drawCircle(int x, int y, int radius);
    void drawDisk(int x, int y, int radius);

    inline std::pair<int, int> getSize() const { return size_; }


private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;
    std::pair<int, int> size_;

};