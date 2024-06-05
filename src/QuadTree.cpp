#include "QuadTree.hpp"

QuadTree::QuadTree(float x1, float y1, float x2, float y2, int level, int sizeMax)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2), level_(level), sizeMax_(sizeMax), northWest_(nullptr), northEast_(nullptr), southWest_(nullptr), southEast_(nullptr), points_()
{

}

QuadTree::~QuadTree()
{
    northWest_.reset();
    northEast_.reset();
    southWest_.reset();
    southEast_.reset();
    points_.clear();
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
        for (auto const& point : points_)
        {
            insertRecursive(point);
        }
        points_.clear();
    }
}

void QuadTree::insertRecursive(CellularUnit const& unit)
{
    if (points_.size() < sizeMax_ && northWest_ == nullptr)
    {
        points_.push_back(unit);
    }
    else
    {
        if (northWest_ == nullptr)
        {
            subdivide();
        }

        if (unit.getX() < (x1_ + x2_) / 2)
        {
            if (unit.getY() < (y1_ + y2_) / 2)
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
            if (unit.getY() < (y1_ + y2_) / 2)
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

void QuadTree::renderRecursive(RendererHandler const& renderer)
{
    renderer.drawrect(x1_, y1_, x2_, y2_);

    if (northWest_ != nullptr)
    {
        northWest_->renderRecursive(renderer, color, coef);
        northEast_->renderRecursive(renderer, color, coef);
        southWest_->renderRecursive(renderer, color, coef);
        southEast_->renderRecursive(renderer, color, coef);
    }
    return;
}




