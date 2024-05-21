#include "../include/God.hpp"




God::God(int nbColumns, int nbLines, int nbCellularUnits) : nbColumns_(nbColumns), nbLines_(nbLines), universeState_(UniverseState::PAUSED)
{
    for (int i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() % nbColumns_, rand() % nbLines_));
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
        else if (e.key.keysym.sym == SDLK_r)
        {
            newUniverse(100);
        }
    }
    
    }
    return universeState_;

}   

void God::newUniverse(int nbCellularUnits)
{
    cellularUnits_.clear();
    for (int i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() % nbColumns_, rand() % nbLines_));
    }
}