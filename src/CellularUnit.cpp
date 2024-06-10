#include "../include/CellularUnit.hpp"

CellularUnit::CellularUnit(float x, float y, long int id)
    : coords_(std::pair<float, float>(x, y)), velocity_(std::pair<float, float>(0.0 , 0.0)), id_(id)
{
    std::cout << " CellularUnit id " << id_ << " created : " << coords_.first << " " << coords_.second << std::endl;
    velocity_.first = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(VELOCITY_MAX)));
    //velocity_.first = 1.0;

    // Angle between 0 and 2*PI
    velocity_.second  = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(2*M_PI)));
}

CellularUnit::~CellularUnit()
{
    //std::cout << " CellularUnit destroyed : " << coords_.first << " " << coords_.second << std::endl;
}


void CellularUnit::move()
{
    coords_.first += velocity_.first * cos(velocity_.second) * CELL_SIZE;
    coords_.second += velocity_.first * sin(velocity_.second) * CELL_SIZE;

    if (coords_.first < 0)
    {
        coords_.first = (SCREEN_X) - coords_.first;
    }
    else if (coords_.first > (SCREEN_X))
    {
        coords_.first = coords_.first - (SCREEN_X);
    }

    if (coords_.second < 0)
    {
        coords_.second = (SCREEN_Y) - coords_.second;
    }
    else if (coords_.second > (SCREEN_Y))
    {
        coords_.second = coords_.second - (SCREEN_Y);
    }
}

void CellularUnit::updateVelocity()
{
    switch(behavior_)
    {
        case CellBehavior::NONE:
            break;
        case CellBehavior::ACCELERATE:
            velocity_.first += 0.1;
            break;
        case CellBehavior::DECELERATE:
            velocity_.first -= 0.1;
            break;
        case CellBehavior::TURN:
            velocity_.second += 0.1;
            break;
        default:
            break;
    }
}

float CellularUnit::distanceTo(const CellularUnit *unit) const
{
    return sqrt(pow(unit->getX() - coords_.first, 2) + pow(unit->getY() - coords_.second, 2));
}

float CellularUnit::angleTo(const CellularUnit *unit) const
{
    return atan2(unit->getY() - coords_.second, unit->getX() - coords_.first);
}

bool CellularUnit::hasCollided(const CellularUnit *unit) const
{
    return (distanceTo(unit) < DISTANCE_COLLISION);
}

bool CellularUnit::hasCollidedNeighbor() const
{
    for (const CellularUnit* neighbor : neighbors_)
    {
        if (hasCollided(neighbor))
        {
            return 1;
        }
    }
    return 0;
}