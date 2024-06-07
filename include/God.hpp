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
    void destroyUniverse();

    void createQuadTree();
    void moveCellularUnits();
    void addCell(int x, int y);
    void updateNeighbours();
    void detectCollisions();
    void removeDeadCells();

    inline const std::vector<CellularUnit>* getCellularUnits() const { return &cellularUnits_; }
    inline float getNbColumns() const { return screenX_;; }
    inline float getNbLines() const { return screenY_;; }
    inline QuadTree* getQuadTree() const { return quadTree_.get(); }
    inline void switchDetectCollision() { detectCollision_ = !detectCollision_; }


private:
    std::vector<CellularUnit> cellularUnits_;
    float screenX_;
    float screenY_;

    std::unique_ptr<QuadTree> quadTree_;
    long int idCounter_ = 0;

    bool detectCollision_;
};



