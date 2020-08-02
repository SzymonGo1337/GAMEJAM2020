#include "collisionDetector.hpp"
#include "collisionDetector.hpp"

bool Collider::detectCollisionWith(Collider *other){
    return detectCollision(this, other);
}