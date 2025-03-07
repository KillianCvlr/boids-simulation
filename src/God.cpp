#include "../include/God.hpp"


God::God(float universeX, float universeY, size_t nbCellularUnits) :universeX_(universeX), universeY_(universeY), quadTree_(nullptr), indexCellularUnits_(nbCellularUnits)
{
    // Initializes the cellularUnits_ vector with newly created cells
    for (size_t i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() %  (int)universeX_, rand() %  (int)universeY_, i));
        std::cout << "FInito ";
    }
}

God::~God()
{
    cellularUnits_.clear();
}

void God::updateUniverse()
{
    moveCellularUnits();
    quadTree_.reset(new QuadTree(0, 0, universeX_, universeY_, 0));
    createQuadTree();
    updateNeighbours(); 
    return;
}

void God::newUniverse(size_t nbCellularUnits)
{
    cellularUnits_.clear();
    for (size_t i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() % (int)universeX_, rand() %  (int)universeY_, i));
    }
    indexCellularUnits_ = nbCellularUnits;
    quadTree_.reset(new QuadTree(0, 0, universeX_, universeY_, 0));
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