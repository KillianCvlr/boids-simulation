#include <iostream>
#include <memory>

class CellularUnit
{

public:
    CellularUnit(int x, int y, bool isAlive = true);
    ~CellularUnit();

    inline std::pair<int, int> getCoords() const { return coords_; }
    inline int getX() const { return coords_.first; }
    inline int getY() const { return coords_.second; }
    inline void setCoords(int x, int y) { coords_ = std::pair<int, int>(x, y); }
    inline bool isAlive() const { return isAlive_; }
    inline void setAlive(bool isAlive) { isAlive_ = isAlive; }


private:
    std::pair<int, int> coords_;
    bool isAlive_;
};


