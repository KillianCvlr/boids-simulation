#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>

#include "God.hpp" 

#define SDL_RED 255, 0, 0, 255
#define SDL_GREEN 0, 255, 0, 255
#define SDL_BLUE 0, 0, 255, 255
#define SDL_BLACK 0, 0, 0, 255
#define SDL_WHITE 255, 255, 255, 255
#define SDL_PURPLE 255, 0, 255, 255
#define SDL_YELLOW 255, 255, 0, 255
#define SDL_CYAN 0, 255, 255, 255
#define SDL_ORANGE 255, 165, 0, 255

#define CELL_SIZE 5


class RenderHandler {
public:
    RenderHandler(char const *title, int const width, int const height);
    ~RenderHandler();

    void renderUniverse(God const& god);
    void renderGrid(God const& god);
    void renderCells(God const& god);

    inline std::pair<int, int> getSize() const { return m_size; }


private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    std::pair<int, int> m_size;
};