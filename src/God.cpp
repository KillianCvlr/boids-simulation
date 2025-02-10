#include "../include/God.hpp"


God::God(float nbColumns, float nbLines, int nbCellularUnits) :screenX_(nbColumns), screenY_(nbLines), quadTree_(nullptr)
{
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

void God::newUniverse(int nbCellularUnits)
{
    cellularUnits_.clear();
    for (size_t i = 0; i < nbCellularUnits; i++)
    {
        std::cout << "Creating new CellularUnit" << std::endl;
        cellularUnits_.push_back(CellularUnit(rand() % (int)screenX_, rand() %  (int)screenY_, i));
        std::cout << "New CellularUnit created : " << std::endl;
    }
    indexCellularUnits_ = nbCellularUnits;
    quadTree_.reset(new QuadTree(0, 0, screenX_, screenY_, 0));
    createQuadTree();
}

void God::destroyUniverse()
{
    cellularUnits_.clear();
}

void God::createQuadTree()
{
    for (int i = 0; i < cellularUnits_.size(); i++)
    {
        quadTree_->insertRecursive(&cellularUnits_[i]);
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

void God::addCell(int x, int y)
{
    cellularUnits_.push_back(CellularUnit(x, y, indexCellularUnits_));
    indexCellularUnits_ ++;
    return;
}

void God::updateNeighbours()
{
    for (int i = 0; i < cellularUnits_.size(); i++)
    {
        cellularUnits_[i].clearNeighbors();
        quadTree_->circleQuerryRecursive(&cellularUnits_[i]);
    }
    return;
}