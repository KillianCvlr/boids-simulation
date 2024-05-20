#include "../include/RenderHandler.hpp"

RenderHandler::RenderHandler(char const *title, int const width, int const height)
    : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer), m_size(std::pair<int, int>(width, height))
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    std::cout << "SDL_Init Success" << std::endl;

    m_window.reset(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN));
    if (m_window == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (m_renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    std::cout << "SDL_CreateRenderer Success" << std::endl;

    // Chargement des textures
    

    std::cout << "Textures loaded" << std::endl;


}

RenderHandler::~RenderHandler()
{
    SDL_DestroyRenderer(m_renderer.get());
    SDL_DestroyWindow(m_window.get());
    SDL_Quit();
}


void RenderHandler::renderUniverse(God god)
{
    SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_renderer.get());

    for (auto &cellularUnit : god.getCellularUnits())
    {
        SDL_Rect rect = {cellularUnit.getCoords().first * 10, cellularUnit.getCoords().second * 10, 10, 10};
        
        
        if (cellularUnit.isAlive())
        {
            SDL_SetRenderDrawColor(m_renderer.get(), SDL_GREEN);
        }
        else
        {
            SDL_SetRenderDrawColor(m_renderer.get(), SDL_RED);
        }
        SDL_RenderFillRect(m_renderer.get(), &rect);
    }

    SDL_RenderPresent(m_renderer.get());
    return;
}

void RenderHandler::renderGrid(God god)
{
    SDL_SetRenderDrawColor(m_renderer.get(), SDL_CYAN - 200);

    for (int i = 0; i < god.getUniverseLength(); i++)
    {
        SDL_RenderDrawLine(m_renderer.get(), 0, i * 10, god.getUniverseLength() * 10, i * 10);
    }

    for (int i = 0; i < god.getUniverseWidth(); i++)
    {
        SDL_RenderDrawLine(m_renderer.get(), i * 10, 0, i * 10, god.getUniverseWidth() * 10);
    }

    SDL_RenderPresent(m_renderer.get());
    return;
}
