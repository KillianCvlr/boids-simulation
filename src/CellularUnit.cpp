#include "../include/CellularUnit.hpp"

CellularUnit::CellularUnit(int x, int y, bool isAlive)
    : coords_(std::pair<int, int>(x, y))
{
    std::cout << " CellularUnit created : " << coords_.first << " " << coords_.second << std::endl;
}

CellularUnit::~CellularUnit()
{
}