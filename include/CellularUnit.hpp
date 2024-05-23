#include <iostream>
#include <memory>
#include <utility>
#include <cmath>

#include "DefaultValues.hpp"


class CellularUnit
{

public:
    CellularUnit(int x, int y);
    ~CellularUnit();

    void move();

    inline std::pair<int, int> getCoords() const { return coords_; }
    inline int getX() const { return coords_.first; }
    inline int getY() const { return coords_.second; }
    inline void setCoords(int x, int y) { coords_ = std::pair<int, int>(x, y); }
    inline void setVelocity(float x, float y) { velocity_ = std::pair<float, float>(x, y); }
    inline std::pair<float, float> getVelocity() const { return velocity_; }


private:
    std::pair<int, int> coords_;
    std::pair<float, float> velocity_;

};


