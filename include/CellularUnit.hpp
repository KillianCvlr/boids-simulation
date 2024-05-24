#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <cmath>
#include <list>

#include "DefaultValues.hpp"


enum class CellBehavior
{
    NONE,
    ACCELERATE,
    DECELERATE,
    TURN
};

class CellularUnit
{

public:
    CellularUnit(float x, float y);
    ~CellularUnit();

    void move();
    void updateVelocity();

    inline std::pair<float, float> getCoords() const { return coords_; }
    inline float getX() const { return coords_.first; }
    inline float getY() const { return coords_.second; }
    inline void setCoords(float x, float y) { coords_ = std::pair<float, float>(x, y); }
    inline void setVelocity(float x, float y) { velocity_ = std::pair<float, float>(x, y); }
    inline std::pair<float, float> getVelocity() const { return velocity_; }


private:
    std::pair<float, float> coords_;
    // Vecocity is a pair of float, the first float is the speed, the second is the angle
    std::pair<float, float> velocity_;
    std::list<std::pair<float, float>> messages_;

    CellBehavior behavior_;

};


