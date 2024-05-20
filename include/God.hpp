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
    God(int length, int width, int nbCellularUnits);
    ~God();

    UniverseState updateUniverse(SDL_Event e);
    UniverseState handleMe(SDL_Event e);

    inline std::vector<CellularUnit> getCellularUnits() const { return cellularUnits_; }
    inline int getUniverseLength() const { return UniverseLength_; }
    inline int getUniverseWidth() const { return UniverseWidth_; }
    inline UniverseState getUniverseState() const { return universeState_; }

private:
    std::vector<CellularUnit> cellularUnits_;
    int UniverseLength_;
    int UniverseWidth_;
    UniverseState universeState_;
};



