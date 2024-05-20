#include "../include/God.hpp"




God::God(int length, int width, int nbCellularUnits) : UniverseLength_(length), UniverseWidth_(width), universeState_(UniverseState::PAUSED)
{
    for (int i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() % length, rand() % width));
    }
}


God::~God()
{
    cellularUnits_.clear();
}

UniverseState God::updateUniverse(SDL_Event e)
{
    int nbCellularUnits = cellularUnits_.size();
    int randomCellularUnitIndex = rand() % nbCellularUnits;
    cellularUnits_[randomCellularUnitIndex].setAlive(!cellularUnits_[randomCellularUnitIndex].isAlive());
    std::cout << "CellularUnit " << randomCellularUnitIndex << " is now " << (cellularUnits_[randomCellularUnitIndex].isAlive() ? "alive" : "dead") << std::endl;
    handleMe(e);
    return universeState_;
}

UniverseState God::handleMe(SDL_Event e)
{
    while (SDL_PollEvent(&e))
    {
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_SPACE)
        {
            universeState_ = ((universeState_ == UniverseState::PAUSED) ? UniverseState::ALIVE : UniverseState::PAUSED);
        }
        else if (e.key.keysym.sym == SDLK_ESCAPE)
        {
            universeState_ = UniverseState::DEAD;
        }
    }
    
    }
    return universeState_;

}   