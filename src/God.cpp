#include "../include/God.hpp"


God::God(float nbColumns, float nbLines, int nbCellularUnits) :screenX_(nbColumns), screenY_(nbLines), quadTree_(nullptr), idCounter_(nbCellularUnits)
{
    for (int i = 0; i < nbCellularUnits; i++)
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
    removeDeadCells();
    moveCellularUnits();
    quadTree_.reset(new QuadTree(0, 0, screenX_, screenY_, 0));
    createQuadTree();
    updateNeighbours(); 
    if (detectCollision_) detectCollisions();
    return;
}

void God::newUniverse(int nbCellularUnits)
{
    cellularUnits_.clear();
    for (int i = 0; i < nbCellularUnits; i++)
    {
        cellularUnits_.push_back(CellularUnit(rand() % (int)screenX_, rand() %  (int)screenY_, i));
    }
    idCounter_ = nbCellularUnits;
    quadTree_.reset(new QuadTree(0, 0, screenX_, screenY_, 0));
    createQuadTree();
}

void God::destroyUniverse()
{
    cellularUnits_.clear();
    idCounter_ = 0;
}

void God::createQuadTree()
{
    for (int i = 0; i < (int)cellularUnits_.size(); i++)
    {
        quadTree_->insertRecursive(cellularUnits_[i].getAddress());
    }
    return;
}

void God::moveCellularUnits()
{
    for (int i = 0; i < (int)cellularUnits_.size(); i++)
    {
        cellularUnits_[i].move();
    }
    return;
}

void God::addCell(int x, int y)
{
    cellularUnits_.push_back(CellularUnit(x, y, idCounter_++));
    return;
}

void God::updateNeighbours()
{
    for (int i = 0; i < (int)cellularUnits_.size(); i++)
    {
        cellularUnits_[i].clearNeighbors();
        quadTree_->circleQuerryRecursive(&cellularUnits_[i]);
    }
    return;
}

void God::detectCollisions()
{
    for (int i = 0; i < (int)cellularUnits_.size(); i++)
    {
        if (cellularUnits_[i].hasCollidedNeighbor())
        {
            cellularUnits_[i].setDead();
            std::cout << "Cell " << cellularUnits_[i].getId() << " has died" << std::endl;
        }
    }
}

void God::removeDeadCells()
{
    cellularUnits_.erase(std::remove_if(cellularUnits_.begin(), cellularUnits_.end(), [](CellularUnit &cell) { return !cell.isAlive(); }), cellularUnits_.end());
}