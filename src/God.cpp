#include "../include/God.hpp"




God::God(float nbColumns, float nbLines, int nbCellularUnits) : screenX_(nbColumns), screenY_(nbLines), quadTree_(nullptr)
{
    for (int i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() %  (int)screenX_, rand() %  (int)screenY_));
    }
}


God::~God()
{
    cellularUnits_.clear();
}

void God::updateUniverse()
{
    moveCellularUnits();
    quadTree_.reset();
    createQuadTree();
    return;
}

void God::newUniverse(int nbCellularUnits)
{
    cellularUnits_.clear();
    for (int i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() % (int)screenX_, rand() %  (int)screenY_));
    }
}

void God::createQuadTree()
{
    std::unique_ptr<QuadTree> quadTree = std::make_unique<QuadTree>(0, 0, screenX_, screenY_, 0, 4);
    for (int i = 0; i < cellularUnits_.size(); i++)
    {
        quadTree->insertRecursive(cellularUnits_[i]);
    }
    return;
}

void God::moveCellularUnits()
{
    for (int i = 0; i < cellularUnits_.size(); i++)
    {
        cellularUnits_[i].move();
    }
    return;
}