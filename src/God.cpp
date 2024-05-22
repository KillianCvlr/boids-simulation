#include "../include/God.hpp"




God::God(int nbColumns, int nbLines, int nbCellularUnits) : nbColumns_(nbColumns), nbLines_(nbLines)
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

void God::updateUniverse(SDL_Event e)
{
    int nbCellularUnits = cellularUnits_.size();
    int randomCellularUnitIndex = rand() % nbCellularUnits;
    //std::cout << "CellularUnit " << randomCellularUnitIndex << " is now " << (cellularUnits_[randomCellularUnitIndex].isAlive() ? "alive" : "dead") << std::endl;
    return;
}

void God::newUniverse(int nbCellularUnits)
{
    cellularUnits_.clear();
    for (int i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() % nbColumns_, rand() % nbLines_));
    }
}