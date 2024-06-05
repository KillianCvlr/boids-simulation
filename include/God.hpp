#pragma once

#include "CellularUnit.hpp"
#include "QuadTree.hpp"

#include "SDL.h"
#include <iostream>
#include <memory>
#include <vector>



class God
{

public:
    God(float nbColulmns, float nbLines, int nbCellularUnits);
    ~God();

    void updateUniverse();
    void newUniverse(int nbCellularUnits);

    void createQuadTree();
    void moveCellularUnits();

    inline std::vector<CellularUnit> getCellularUnits() const { return cellularUnits_; }
    inline float getNbColumns() const { return screenX_;; }
    inline float getNbLines() const { return screenY_;; }

private:
    std::vector<CellularUnit> cellularUnits_;
    float screenX_;
    float screenY_;

    std::unique_ptr<QuadTree> quadTree_;
};



