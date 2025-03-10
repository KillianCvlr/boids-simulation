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
    FLOCKING,
    DECELERATE,
    PERIPHERICAL_VIEW
};

class CellularUnit
{

public:
    CellularUnit(float x, float y, size_t id);
    ~CellularUnit();

    void move();
    void updateVelocity();
    void updateAccelPeriphericalView();
    void updateAccelFlocking();

    float getAngleToNeighbor(const CellularUnit *);
    float getDistanceToNeighbor(const CellularUnit *);

    inline std::pair<float, float> getCoords() const { return coords_; }
    inline float getX() const { return coords_.first; }
    inline float getY() const { return coords_.second; }
    inline void setCoords(float x, float y) { coords_ = std::pair<float, float>(x, y); }
    inline void setVelocity(float x, float y) { velocity_ = std::pair<float, float>(x, y); }
    inline const std::pair<float, float> getVelocity() const { return velocity_; }
    inline const std::pair<float, float> getAcceleration() const { return acceleration_; }
    inline void addNeighbor(const CellularUnit *unit) { neighbors_.push_back(unit); }
    inline void clearNeighbors() { neighbors_.clear(); }
    inline const std::list<const CellularUnit *> getNeighbors() const { return neighbors_; }
    inline float getCellAngle() const {return cellAngle_;}
    inline void actualizeAngle() {cellAngle_ = atan2f(velocity_.second, velocity_.first);}
    inline size_t getId(){return id_;}

private:
    // Coords is a pair of float that keeps the coordinates of the cell
    std::pair<float, float> coords_;

    // Velocity is a pair of float representing the x and y values of the velocity vector
    std::pair<float, float> velocity_;

    // CellAngle is the representation of the angle to the horizontal of the Cell
    // Stocked for perfomance issues
    float cellAngle_;

    // Acceleration is a pair of float representing the x and y values of the Acceleration vector
    std::pair<float, float> acceleration_;
    std::list<const CellularUnit *> neighbors_ = {};
    size_t id_;

    CellBehavior behavior_;

};


