#include "../include/CellularUnit.hpp"

CellularUnit::CellularUnit(float x, float y)
    : coords_(std::pair<float, float>(x, y)), velocity_(std::pair<float, float>(0.0 , 0.0))
{
    std::cout << " CellularUnit created : " << coords_.first << " " << coords_.second << std::endl;
    // velocity_.first = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(10.0)));
    velocity_.first = 1.0;

    // Angle between 0 and 2*PI
    velocity_.second  = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(2*M_PI)));
}

CellularUnit::~CellularUnit()
{
}


void CellularUnit::move()
{
    coords_.first += velocity_.first * cos(velocity_.second);
    coords_.second += velocity_.first * sin(velocity_.second);

    if (coords_.first < 0)
    {
        coords_.first = (SCREEN_X / CELL_SIZE) - coords_.first;
    }
    else if (coords_.first > (SCREEN_X / CELL_SIZE))
    {
        coords_.first = coords_.first - (SCREEN_X / CELL_SIZE);
    }

    if (coords_.second < 0)
    {
        coords_.second = (SCREEN_Y / CELL_SIZE) - coords_.second;
    }
    else if (coords_.second > (SCREEN_Y / CELL_SIZE))
    {
        coords_.second = coords_.second - (SCREEN_Y / CELL_SIZE);
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