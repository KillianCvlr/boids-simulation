#pragma once

#include "CellularUnit.hpp"
#include "QuadTree.hpp"

#include <iostream>
#include <memory>
#include <vector>



class God
{

public:
    God(float universeX, float universeY, size_t nbCellularUnits);
    ~God();

    void updateUniverse();
    void newUniverse(size_t nbCellularUnits);
    void destroyUniverse();

    void createQuadTree();
    void moveCellularUnits();
    void addCell(int x, int y);
    void updateNeighbours();

    inline const std::vector<CellularUnit>* getCellularUnits() const { return &cellularUnits_; }
    inline float getUniverseX() const { return universeX_;; }
    inline float getUniverseY() const { return universeY_;; }
    inline QuadTree* getQuadTree() const { return quadTree_.get(); }
    inline size_t getIndexCellularUnits() const {return indexCellularUnits_;}

private:
    std::vector<CellularUnit> cellularUnits_;
    float universeX_;
    float universeY_;

    std::unique_ptr<QuadTree> quadTree_;
    size_t indexCellularUnits_;
};



