#pragma once

#include <SDL.h>
#include <iostream>
#include <memory>

class RenderHandler {
public:
    RenderHandler(char const *title, int const width, int const height);
    ~RenderHandler();

    inline std::pair<int, int> getSize() const { return m_size; }
    SDL_Texture* loadTexture(char const *path, bool const transparancy = false);


private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
    std::pair<int, int> m_size;
};