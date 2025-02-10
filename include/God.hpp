#pragma once

#include "CellularUnit.hpp"
#include "QuadTree.hpp"

#include <iostream>
#include <memory>
#include <vector>



class God
{

public:
    God(float nbColulmns, float nbLines, size_t nbCellularUnits);
    ~God();

    void updateUniverse();
    void newUniverse(size_t nbCellularUnits);
    void destroyUniverse();

    void createQuadTree();
    void moveCellularUnits();
    void addCell(int x, int y);
    void updateNeighbours();

    inline const std::vector<CellularUnit>* getCellularUnits() const { return &cellularUnits_; }
    inline float getNbColumns() const { return screenX_;; }
    inline float getNbLines() const { return screenY_;; }
    inline QuadTree* getQuadTree() const { return quadTree_.get(); }

private:
    std::vector<CellularUnit> cellularUnits_;
    float screenX_;
    float screenY_;

    std::unique_ptr<QuadTree> quadTree_;
    size_t indexCellularUnits_;
};



