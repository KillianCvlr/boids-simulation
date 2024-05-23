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

void God::updateUniverse()
{
    moveCellularUnits();
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

void God::moveCellularUnits()
{
    for (int i = 0; i < cellularUnits_.size(); i++)
    {
        cellularUnits_[i].move();
    }
    return;
}