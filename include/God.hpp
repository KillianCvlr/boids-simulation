#pragma once

#include "CellularUnit.hpp"

#include "SDL.h"
#include <iostream>
#include <memory>
#include <vector>



class God
{

public:
    God(int nbColulmns, int nbLines, int nbCellularUnits);
    ~God();

    void updateUniverse(SDL_Event e);
    void newUniverse(int nbCellularUnits);

    inline std::vector<CellularUnit> getCellularUnits() const { return cellularUnits_; }
    inline int getNbColumns() const { return nbColumns_; }
    inline int getNbLines() const { return nbLines_; }

private:
    std::vector<CellularUnit> cellularUnits_;
    int nbColumns_;
    int nbLines_;
};



