#include "../include/RenderHandler.hpp"

RenderHandler::RenderHandler(char const *title, int const width, int const height)
    : window_(nullptr, SDL_DestroyWindow), renderer_(nullptr, SDL_DestroyRenderer), size_(std::pair<int, int>(width, height))
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    std::cout << "SDL_Init Success" << std::endl;

    window_.reset(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN));
    if (window_ == nullptr)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer_.reset(SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if (renderer_ == nullptr)
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
    SDL_DestroyRenderer(renderer_.get());
    SDL_DestroyWindow(window_.get());
    SDL_Quit();
}


void RenderHandler::renderUniverse(God const& god)
{
    SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer_.get());
    renderCells(god);   

    SDL_RenderPresent(renderer_.get());
    return;
}


void RenderHandler::renderCells(God const& god)
{
    for (auto &cellularUnit : god.getCellularUnits())
    {
        
        SDL_SetRenderDrawColor(renderer_.get(), SDL_AQUA);

        drawDisk(cellularUnit.getCoords().first * CELL_SIZE, cellularUnit.getCoords().second * CELL_SIZE, CELL_SIZE / 2);
    }
    return;
}

void RenderHandler::drawCircle(int centreX, int centreY, int radius)
{
   const int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer_.get(), centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer_.get(), centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer_.get(), centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer_.get(), centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer_.get(), centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer_.get(), centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer_.get(), centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer_.get(), centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void RenderHandler::drawDisk(int x1, int y1, int radius)
{
    for (int i = 0; i < radius; i++)
    {
        drawCircle(x1, y1, i);
    }
    return;
}