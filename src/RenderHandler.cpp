#include "../include/RenderHandler.hpp"

RenderHandler::RenderHandler(char const *title, int const width, int const height)
    : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer), m_size(std::pair<int, int>(width, height)), showGrid_(true)
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


void RenderHandler::renderUniverse(God const& god)
{
    SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(m_renderer.get());
    if (showGrid_) renderGrid(god);
    renderCells(god);   

    SDL_RenderPresent(m_renderer.get());
    return;
}

void RenderHandler::renderGrid(God const& god)
{
    SDL_SetRenderDrawColor(m_renderer.get(), SDL_CYAN - 200);

    for (int i = 0; i < god.getNbColumns(); i++)
    {
        SDL_RenderDrawLine(m_renderer.get(), i * CELL_SIZE, 0, i * CELL_SIZE, god.getNbLines() * CELL_SIZE);
    }

    for (int i = 0; i < god.getNbLines(); i++)
    {
        SDL_RenderDrawLine(m_renderer.get(), 0, i * CELL_SIZE, god.getNbColumns() * CELL_SIZE, i * CELL_SIZE);
    }

    return;
}

void RenderHandler::renderCells(God const& god)
{
    for (auto &cellularUnit : god.getCellularUnits())
    {
        SDL_Rect rect = {cellularUnit.getCoords().first * CELL_SIZE, cellularUnit.getCoords().second * CELL_SIZE, CELL_SIZE, CELL_SIZE};
        
        
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
    return;
}
