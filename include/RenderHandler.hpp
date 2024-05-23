#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>

#include "God.hpp" 

#include "SDLColors.hpp"


class RenderHandler {
public:
    RenderHandler(char const *title, int const width, int const height);
    ~RenderHandler();

    void renderUniverse(God const& god);
    void renderGrid(God const& god);
    void renderCells(God const& god);

    inline void switchGrid() { showGrid_ = !showGrid_; }
    inline std::pair<int, int> getSize() const { return m_size; }


private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    std::pair<int, int> m_size;

    bool showGrid_;
};