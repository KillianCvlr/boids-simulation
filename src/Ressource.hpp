#include "Ressource.hpp"

Ressource::Ressource(int x, int y, RessourceType type, int quantity)
    : CellularUnit(x, y, true), type_(type), quantity_(quantity)
{
    std::cout << "Ressource created : " << coords_.first << " " << coords_.second << std::endl;
}

Ressource::~Ressource()
{
}
