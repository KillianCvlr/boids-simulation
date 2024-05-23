#include "../include/CellularUnit.hpp"

CellularUnit::CellularUnit(float x, float y)
    : coords_(std::pair<float, float>(x, y)), velocity_(std::pair<float, float>(0.0 , 0.0))
{
    std::cout << " CellularUnit created : " << coords_.first << " " << coords_.second << std::endl;
    // bitesexqueue!!!! velocity_.first = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(10.0)));
    velocity_.first = 3.0;

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
        coords_.first = SCREEN_X - coords_.first;
    }
    else if (coords_.first > SCREEN_X)
    {
        coords_.first = coords_.first - SCREEN_X;
    }

    if (coords_.second < 0)
    {
        coords_.second = SCREEN_Y - coords_.second;
    }
    else if (coords_.second > SCREEN_Y)
    {
        coords_.second = coords_.second - SCREEN_Y;
    }
}