#pragma once

#include "CellularUnit.hpp"
#include "QuadTree.hpp"

#include <iostream>
#include <memory>
#include <vector>



class God
{

public:
    God(int nbColulmns, int nbLines, size_t nbCellularUnits);
    ~God();

    void updateUniverse();
    void newUniverse(size_t nbCellularUnits);
    void destroyUniverse();

    void createQuadTree();
    void moveCellularUnits();
    void addCell(int x, int y);
    void updateNeighbours();

    inline const std::vector<CellularUnit>* getCellularUnits() const { return &cellularUnits_; }
    inline int getNbColumns() const { return screenX_;; }
    inline int getNbLines() const { return screenY_;; }
    inline QuadTree* getQuadTree() const { return quadTree_.get(); }
    inline size_t getIndexCellularUnits() const {return indexCellularUnits_;}

private:
    std::vector<CellularUnit> cellularUnits_;
    int screenX_;
    int screenY_;

    std::unique_ptr<QuadTree> quadTree_;
    size_t indexCellularUnits_;
};



