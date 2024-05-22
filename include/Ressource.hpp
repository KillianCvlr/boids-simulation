#include "CelluularUnit.hpp"

enum class RessourceType
{
    FOOD,
    WATER,
    WOOD,
    STONE
};


class Ressource : public CellularUnit
{


public:
    Ressource(int x, int y, RessourceType type, int quantity);
    ~Ressource();

    inline RessourceType getType() const { return type_; }
    inline int getQuantity() const { return quantity_; }
    inline void setQuantity(int quantity) { quantity_ = quantity; }
    inline void addQuantity(int quantity) { quantity_ += quantity; }
    inline void removeQuantity(int quantity) { quantity_ -= quantity; }

private:
    RessourceType type_;
    int quantity_;
};
