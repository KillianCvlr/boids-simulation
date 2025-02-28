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
}

RenderHandler::~RenderHandler()
{
    SDL_DestroyRenderer(renderer_.get());
    SDL_DestroyWindow(window_.get());
    SDL_Quit();
}


void RenderHandler::renderUniverse(const God *god)
{
    SDL_SetRenderDrawColor(renderer_.get(), SDL_BLACK);
    SDL_RenderClear(renderer_.get());
    if (renderCells_) renderCells(god);   
    if (renderFieldViews_) renderFieldViews(god);
    if (renderQuadTree_) renderQuadTree(god);
    if (renderProximity_) renderProximity(god);
    if (renderNeighboringLinks_) renderNeighboringLinks(god);
    if (renderFirst_) renderFirst(god);
    

    SDL_RenderPresent(renderer_.get());
    return;
}

void RenderHandler::renderCell(const CellularUnit cellularUnit){
    // Simple Disk Cell
    //drawDisk(cellularUnit.getCoords().first, cellularUnit.getCoords().second, CELL_SIZE);

    // Triangular Cell
    const float velocityAngle = cellularUnit.getCellAngle();
    float x = cellularUnit.getX();
    float y = cellularUnit.getY();

    const std::vector< SDL_Vertex > verts =
    {
        { SDL_FPoint{ (x + 2*CELL_SIZE *cosf(velocityAngle)), y + 2*CELL_SIZE * sinf(velocityAngle) }, {SDL_AZURE}, SDL_FPoint{ 0, 0 }, },
        { SDL_FPoint{ x + CELL_SIZE *cosf(velocityAngle + M_PI_2), y + CELL_SIZE * sinf(velocityAngle + M_PI_2) }, {SDL_AZURE}, SDL_FPoint{ 0, 0 }, },
        { SDL_FPoint{ x + CELL_SIZE *cosf(velocityAngle - M_PI_2), y + CELL_SIZE * sinf(velocityAngle - M_PI_2) }, {SDL_AZURE}, SDL_FPoint{ 0, 0 }, },
    };

    SDL_RenderGeometry( renderer_.get(), nullptr, verts.data(), 3, nullptr, 0 );

}


void RenderHandler::renderCells(const God *god)
{
    SDL_SetRenderDrawColor(renderer_.get(), SDL_AQUA);

    for (size_t i = 0; i < god->getCellularUnits()->size(); i++)
    {
        const CellularUnit cellularUnit = (*god->getCellularUnits())[i];
        renderCell(cellularUnit);
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
    for (int i = 1; i <= radius; i++)
    {
        drawCircle(x1, y1, i);
    }
    return;
}

void RenderHandler::renderFieldViews(const God *god)
{
    SDL_SetRenderDrawColor(renderer_.get(), SDL_WHITE);
    for (size_t i = 0; i < god->getCellularUnits()->size(); i++)
    {
        CellularUnit cellularUnit = (*god->getCellularUnits())[i];
        renderFieldView(cellularUnit.getX(), cellularUnit.getY(), cellularUnit.getCellAngle());
    }
    return;
}

void RenderHandler::renderFieldView(int x, int y, float angle)
{
    SDL_RenderDrawLine(renderer_.get(), x, y, x + DISTANCE_VIEW * cos(angle + ANGLE_VIEW/2), y + DISTANCE_VIEW * sin(angle + ANGLE_VIEW/2));
    SDL_RenderDrawLine(renderer_.get(), x, y, x + DISTANCE_VIEW * cos(angle - ANGLE_VIEW/2), y + DISTANCE_VIEW * sin(angle - ANGLE_VIEW/2));
    return;
}

void RenderHandler::renderQuadTree(const God *god)
{
    SDL_SetRenderDrawColor(renderer_.get(), SDL_BRONZE);
    god->getQuadTree()->renderRecursive(*this);
    return;
}

void RenderHandler::renderProximity(const God *god)
{
    for (size_t i = 0; i < god->getCellularUnits()->size(); i++)
    {
        CellularUnit cellularUnit = (*god->getCellularUnits())[i];
        cellularUnit.getNeighbors().size() == 0 ? SDL_SetRenderDrawColor(renderer_.get(), SDL_GREEN) : SDL_SetRenderDrawColor(renderer_.get(), SDL_RED);
        drawCircle(cellularUnit.getX(), cellularUnit.getY(), CELL_SIZE + DISTANCE_VIEW);
    }
    return;
}

void RenderHandler::renderNeighboringLinks(const God *god)
{
    SDL_SetRenderDrawColor(renderer_.get(), SDL_CINNAMON);
    for (size_t i = 0; i < god->getCellularUnits()->size(); i++)
    {
        CellularUnit cellularUnit = (*god->getCellularUnits())[i];
        for (auto neighbor : cellularUnit.getNeighbors())
        {
            SDL_RenderDrawLine(renderer_.get(), cellularUnit.getX(), cellularUnit.getY(), neighbor->getX(), neighbor->getY());
        }
    }
    return;
}

void RenderHandler::renderFirst(const God *god)
{
    if(god->getIndexCellularUnits() ==   0) return;
    CellularUnit firstCell = (*god->getCellularUnits())[0];
    float x = firstCell.getX();
    float y = firstCell.getY();

    // Red Line = Velocity
    SDL_SetRenderDrawColor(renderer_.get(), SDL_RUBY);
    SDL_RenderDrawLine(renderer_.get(), x, y,
         x + ((firstCell.getVelocity().first / (MAX_SPEED)) * DISTANCE_VIEW),
         y + ((firstCell.getVelocity().second / (MAX_SPEED)) * DISTANCE_VIEW));
    
    // Green Line = Acceleration
    SDL_SetRenderDrawColor(renderer_.get(), SDL_GREEN);
    SDL_RenderDrawLine(renderer_.get(), x, y,
         x + ((firstCell.getAcceleration().first / MAX_ACCEL) * DISTANCE_VIEW),
         y + ((firstCell.getAcceleration().second / MAX_ACCEL) * DISTANCE_VIEW));
    
    // Neighbors-related metrics so return if none;
    if (firstCell.getNeighbors().size() == 0) return;

    // Yellow Circle for center of mass of neighbors 
    // Grey line for linked neighbors
    // Cinnamon circle for average neighbors velocity
    SDL_SetRenderDrawColor(renderer_.get(), SDL_GREY);
    std::pair<float, float> averageVelocity = {0 ,0 };
    std::pair<float, float> centerOfNeighbors = {0 ,0 };
    for (const auto& neighbor : firstCell.getNeighbors()){
        SDL_RenderDrawLine(renderer_.get(), firstCell.getX(), firstCell.getY(), neighbor->getX(), neighbor->getY());
        
        centerOfNeighbors.first += neighbor->getX() - x;
        centerOfNeighbors.second += neighbor->getY() - y;

        averageVelocity.first += neighbor->getVelocity().first;
        averageVelocity.second += neighbor->getVelocity().second;
    }
    centerOfNeighbors.first = centerOfNeighbors.first / (float)(firstCell.getNeighbors().size());
    centerOfNeighbors.second = centerOfNeighbors.second / (float)(firstCell.getNeighbors().size());

    averageVelocity.first = averageVelocity.first / (float)(firstCell.getNeighbors().size());
    averageVelocity.second = averageVelocity.second / (float)(firstCell.getNeighbors().size());

    SDL_SetRenderDrawColor(renderer_.get(), SDL_YELLOW);
    drawCircle(x + centerOfNeighbors.first, y + centerOfNeighbors.second, CELL_SIZE);

    SDL_SetRenderDrawColor(renderer_.get(), SDL_CINNAMON);
    drawCircle(x + averageVelocity.first, y + averageVelocity.second, CELL_SIZE);

    return;
}



void RenderHandler::drawrect(int x, int y, int x2, int y2)
{   
    SDL_RenderDrawLine(renderer_.get(), x, y, x2, y);
    SDL_RenderDrawLine(renderer_.get(), x2, y, x2, y2);
    SDL_RenderDrawLine(renderer_.get(), x2, y2, x, y2);
    SDL_RenderDrawLine(renderer_.get(), x, y2, x, y);
    return;
}