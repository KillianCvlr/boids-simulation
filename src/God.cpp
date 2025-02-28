#include "../include/God.hpp"


God::God(float nbColumns, float nbLines, size_t nbCellularUnits) :screenX_(nbColumns), screenY_(nbLines), quadTree_(nullptr), indexCellularUnits_(nbCellularUnits)
{
    // Initializes the cellularUnits_ vector with newly created cells
    for (size_t i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() %  (int)screenX_, rand() %  (int)screenY_, i));
    }
}

God::~God()
{
    cellularUnits_.clear();
}

void God::updateUniverse()
{
    moveCellularUnits();
    quadTree_.reset(new QuadTree(0, 0, screenX_, screenY_, 0));
    createQuadTree();
    updateNeighbours(); 
    return;
}

void God::newUniverse(size_t nbCellularUnits)
{
    cellularUnits_.clear();
    for (size_t i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() % (int)screenX_, rand() %  (int)screenY_, i));
    }
    indexCellularUnits_ = nbCellularUnits;
    quadTree_.reset(new QuadTree(0, 0, screenX_, screenY_, 0));
    createQuadTree();
}

void God::destroyUniverse()
{
    cellularUnits_.clear();
    indexCellularUnits_ = 0;
}

void God::createQuadTree()
{
    for (size_t i = 0; i < cellularUnits_.size(); i++)
    {
        quadTree_->insertRecursive(&cellularUnits_[i]);
    }
    return;
}

void God::moveCellularUnits()
{
    for (size_t i = 0; i < cellularUnits_.size(); i++)
    {
        cellularUnits_[i].move();
    }
    return;
}

void God::addCell(int x, int y)
{
    cellularUnits_.push_back(CellularUnit(x, y, indexCellularUnits_));
    indexCellularUnits_ ++;
    return;
}

void God::updateNeighbours()
{
    for (size_t i = 0; i < cellularUnits_.size(); i++)
    {
        cellularUnits_[i].clearNeighbors();
        quadTree_->circleQuerryRecursive(&cellularUnits_[i]);
    }
    return;
}