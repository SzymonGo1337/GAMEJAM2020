#include "rectangleCollider.hpp"
#include <math.h>
#include <typeinfo>
#include "collisionDetector.hpp"

float RectangleCollider::getColliderMaxSizeFromPivot(){
    return sqrtf(pow(width * 0.5f, 2) + pow(height * 0.5f, 2));
}