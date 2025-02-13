#include "../include/CellularUnit.hpp"

//Overloading operators for the std::pair<float, float>
// Addition of two pairs
std::pair<float, float> operator+(const std::pair<float, float>& a, const std::pair<float, float>& b) {
    return {a.first + b.first, a.second + b.second};
}

// Multiplication by scalar (scalar * vecteur)
std::pair<float, float> operator*(float scalar, const std::pair<float, float>& vec) {
    return {scalar * vec.first, scalar * vec.second};
}

// Multiplication by scalar (vecteur * scalar)
std::pair<float, float> operator*(const std::pair<float, float>& vec, float scalar) {
    return {vec.first * scalar, vec.second * scalar};
}

// Multiplication part by part of two vecors
std::pair<float, float> operator*(const std::pair<float, float>& a, const std::pair<float, float>& b) {
    return {a.first * b.first, a.second * b.second};
}

// from x,y to A, theta
std::pair<float, float> cartesianToPolar(const std::pair<float, float>& cartesian) {
    float x = cartesian.first;
    float y = cartesian.second;
    float A = std::sqrt(x * x + y * y);
    float theta = std::atan2(y, x);
    return std::make_pair(A, theta);
}

void normalizePair(std::pair<float, float> vec){
    float norm = std::sqrt(vec.first * vec.first + vec.second * vec.second);
    if (norm != 0.0f) {
        vec.first /= norm;
        vec.second /= norm;
    }
}

/*****************************************************************************/

CellularUnit::CellularUnit(float x, float y, size_t id)
    : coords_(std::pair<float, float>(x, y)), velocity_(std::pair<float, float>(0.0 , 0.0)), 
    acceleration_(std::pair<float, float>(0.0 , 0.0)), 
    neighbors_(std::list<const CellularUnit *>()), id_(id), behavior_(CellBehavior::FLOCKING)
{
    std::cout << " CellularUnit created : " << id << " (" << coords_.first << ", " << coords_.second << ")" << std::endl;
    // velocity_.first = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(10.0)));
    velocity_.first = 1.0;

    // Angle between 0 and 2*PI
    velocity_.second  = static_cast <float> (rand() / (static_cast <float> (RAND_MAX/(2*M_PI))) - M_PIf);
}

CellularUnit::~CellularUnit()
{
    //std::cout << " CellularUnit destroyed : " << coords_.first << " " << coords_.second << std::endl;
}

float CellularUnit::getAngleToNeighbor(const CellularUnit * cellNeighbor){
    return atan2f(cellNeighbor->getY() - coords_.second, cellNeighbor->getX() - coords_.first);
}

float CellularUnit::getDistanceToNeighbor(const CellularUnit * cellNeighbor){
    return (sqrt(pow(cellNeighbor->getX() - this->getX(), 2) + pow(cellNeighbor->getY() - this->getY(), 2)));
}

void CellularUnit::move()
{
    updateVelocity();
    coords_.first += velocity_.first * cos(velocity_.second);
    coords_.second += velocity_.first * sin(velocity_.second);

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

void CellularUnit::updateAccelPeriphericalView(){
    for (std::list<const CellularUnit *>::iterator it = neighbors_.begin(); it != neighbors_.end(); ++it){

        float angleToNeighbor = getAngleToNeighbor(*it);
        float diffAngle = fmodf(velocity_.second - angleToNeighbor, 2*M_PI);
        // Is the neighbor visible ?
        if(fabsf(diffAngle) <= ANGLE_VIEW / 2 ){
            float proximityFactor = (getDistanceToNeighbor(*it) / DISTANCE_VIEW);
            velocity_.second += (proximityFactor) * (diffAngle/10); 
        }      
    }
}

void CellularUnit::updateAccelFlocking(){
    if (neighbors_.size() == 0) return;

    // Coherence :
    std::pair<float, float> centerOfNeighbors = {0 ,0 };
    std::pair<float, float> midVelocity = {0 ,0 };

    for (auto it = neighbors_.begin(); it != neighbors_.end(); ++it){
        const CellularUnit* neighbor = *it;
        centerOfNeighbors.first += getDistanceToNeighbor(neighbor);
        centerOfNeighbors.second -= getAngleToNeighbor(neighbor);

        midVelocity = midVelocity + neighbor->getVelocity();
    }

    centerOfNeighbors = centerOfNeighbors * (1 / neighbors_.size());
    centerOfNeighbors.second = fmodf(centerOfNeighbors.second, 2*M_PI);

    midVelocity = midVelocity * (1 / neighbors_.size());
    midVelocity.second = fmodf(midVelocity.second, 2*M_PI);

    acceleration_ = acceleration_ + (midVelocity *( FORCE_FACTOR));

    acceleration_ = acceleration_ + (centerOfNeighbors *( FORCE_FACTOR));

    // TODOOOOOOOO    

}

void CellularUnit::updateVelocity()
{
    acceleration_ = 0 * acceleration_;
    switch(behavior_)
    {
        case CellBehavior::NONE:
            break;
        case CellBehavior::FLOCKING:
            updateAccelFlocking();
            break;
        case CellBehavior::DECELERATE:
            velocity_.first -= 0.1;
            break;
        case CellBehavior::PERIPHERICAL_VIEW:
            updateAccelPeriphericalView();
            break;
        default:
            break;
    }
    velocity_ = velocity_ + acceleration_;
    velocity_.first = fminf(velocity_.first, MAX_SPEED);
}