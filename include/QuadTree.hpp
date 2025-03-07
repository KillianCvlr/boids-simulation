#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <cmath>
#include <list>

#include "GlobalValues.hpp"
#include "CellularUnit.hpp"

class RenderHandler;

class QuadTree
{
public:
    QuadTree(float x1, float y1, float x2, float y2, int level, int sizeMax = SIZE_MAX_QTREE);
    ~QuadTree();

    void subdivide();
    void insertRecursive(CellularUnit* unit);
    void renderRecursive(RenderHandler& renderHandler);
    void circleQuerryRecursive(CellularUnit* unit);
    void clear();

    

private:

    float x1_;
    float y1_;
    float x2_;
    float y2_;
    int level_;
    int sizeMax_;

    std::unique_ptr<QuadTree> northWest_;
    std::unique_ptr<QuadTree> northEast_;
    std::unique_ptr<QuadTree> southWest_;
    std::unique_ptr<QuadTree> southEast_;

    std::list<CellularUnit *> points_;

};

