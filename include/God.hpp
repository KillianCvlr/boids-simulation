#pragma once

#include "CellularUnit.hpp"

#include "SDL.h"
#include <iostream>
#include <memory>
#include <vector>

enum class UniverseState
{
    DEAD,
    ALIVE,
    PAUSED
};

class God
{

public:
    God(int nbColulmns, int nbLines, int nbCellularUnits);
    ~God();

    UniverseState updateUniverse(SDL_Event e);
    UniverseState handleMe(SDL_Event e);
    void newUniverse(int nbCellularUnits);

    inline std::vector<CellularUnit> getCellularUnits() const { return cellularUnits_; }
    inline int getNbColumns() const { return nbColumns_; }
    inline int getNbLines() const { return nbLines_; }
    inline UniverseState getUniverseState() const { return universeState_; }

private:
    std::vector<CellularUnit> cellularUnits_;
    int nbColumns_;
    int nbLines_;
    UniverseState universeState_;
};



