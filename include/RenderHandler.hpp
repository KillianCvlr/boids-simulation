#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>
#include <cmath>

#include "SDLColors.hpp"

class God;


class RenderHandler {
public:
    RenderHandler(char const *title, int const width, int const height);
    ~RenderHandler();

    void renderUniverse(God const& god);
    void renderCells(God const& god);
    void renderFieldViews(God const& god);
    void renderFieldView(int x, int y, float angle);
    void renderQuadTree(God const& god);

    void drawrect(int x, int y, int x2, int y2);
    void drawCircle(int x, int y, int radius);
    void drawDisk(int x, int y, int radius);

    inline std::pair<int, int> getSize() const { return size_; }


private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;
    std::pair<int, int> size_;

};