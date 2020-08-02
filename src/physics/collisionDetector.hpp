#pragma once

#include "collider.hpp"
#include "rectangleCollider.hpp"
#include "circleCollider.hpp"

bool detectCollision(Collider *first, Collider *second); //Returns true if colliders are touching each other.
bool detectCollisionBetweenRectangleAndCircle(RectangleCollider *rectangle, CircleCollider *circle); //Returns true if colliders are touching each other.