#include "../include/QuadTree.hpp"
#include "../include/RenderHandler.hpp"

QuadTree::QuadTree(float x1, float y1, float x2, float y2, int level, int sizeMax)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2), level_(level), sizeMax_(sizeMax), northWest_(nullptr), northEast_(nullptr), southWest_(nullptr), southEast_(nullptr), points_()
{

}

QuadTree::~QuadTree()
{
    clear();
}

void QuadTree::subdivide()
{
    float xMid = (x1_ + x2_) / 2;
    float yMid = (y1_ + y2_) / 2;

    northWest_ = std::make_unique<QuadTree>(x1_, y1_, xMid, yMid, level_ + 1, sizeMax_);
    northEast_ = std::make_unique<QuadTree>(xMid, y1_, x2_, yMid, level_ + 1, sizeMax_);
    southWest_ = std::make_unique<QuadTree>(x1_, yMid, xMid, y2_, level_ + 1, sizeMax_);
    southEast_ = std::make_unique<QuadTree>(xMid, yMid, x2_, y2_, level_ + 1, sizeMax_);

    if (points_.size() > 0)
    {
        for (auto cellPoint : points_)
        {
            insertRecursive(cellPoint);
        }
        points_.clear();
    }
}

void QuadTree::insertRecursive(CellularUnit *unit)
{
    if (((int)points_.size() < sizeMax_ && northWest_ == nullptr ) || level_ == MAX_LEVEL_QTREE)
    {
        points_.push_back(unit);
    }
    else
    {
        if (northWest_ == nullptr)
        {
            subdivide();
        }

        if (unit->getX() < (x1_ + x2_) / 2)
        {
            if (unit->getY() < (y1_ + y2_) / 2)
            {
                northWest_->insertRecursive(unit);
            }
            else
            {
                southWest_->insertRecursive(unit);
            }
        }
        else
        {
            if (unit->getY() < (y1_ + y2_) / 2)
            {
                northEast_->insertRecursive(unit);
            }
            else
            {
                southEast_->insertRecursive(unit);
            }
        }
    }
    return;
}

void QuadTree::renderRecursive(RenderHandler & renderer)
{
    renderer.drawrect(x1_, y1_, x2_, y2_);

    if (northWest_ != nullptr)
    {
        northWest_->renderRecursive(renderer);
        northEast_->renderRecursive(renderer);
        southWest_->renderRecursive(renderer);
        southEast_->renderRecursive(renderer);
    }
    return;
}

void QuadTree::circleQuerryRecursive(CellularUnit *unit)
{
    if (unit->getX() - DISTANCE_VIEW > x2_ || unit->getX() + DISTANCE_VIEW < x1_ || unit->getY() - DISTANCE_VIEW > y2_ || unit->getY() + DISTANCE_VIEW < y1_)
    {
        return;
    }
    else
    {
        if (northWest_ == nullptr)
        {
            for (auto cellPoint : points_)
            {
                if (sqrt(pow(cellPoint->getX() - unit->getX(), 2) + pow(cellPoint->getY() - unit->getY(), 2)) < DISTANCE_VIEW &&
                    unit->getId() != cellPoint->getId())
                {
                    unit->addNeighbor(cellPoint);
                }
            }
        }
        else
        {
            northWest_->circleQuerryRecursive(unit);
            northEast_->circleQuerryRecursive(unit);
            southWest_->circleQuerryRecursive(unit);
            southEast_->circleQuerryRecursive(unit);
        }
    }
}

void QuadTree::clear()
{
    northWest_.reset();
    northEast_.reset();
    southWest_.reset();
    southEast_.reset();
    return;
}




