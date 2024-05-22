#include <iostream>
#include <memory>

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT

};

class CellularUnit
{

public:
    CellularUnit(int x, int y, bool isAlive = true);
    ~CellularUnit();

    inline std::pair<int, int> getCoords() const { return coords_; }
    inline int getX() const { return coords_.first; }
    inline int getY() const { return coords_.second; }
    inline void setCoords(int x, int y) { coords_ = std::pair<int, int>(x, y); }

private:
    std::pair<int, int> coords_;
};


