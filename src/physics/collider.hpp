#pragma once

#include <SFML/System/Vector2.hpp>

class Collider{
    public:
        sf::Vector2f position;
        sf::Vector2f scale;
        float rotation;
    public:
        virtual float getColliderMaxSizeFromPivot() = 0; //Returns point in collider, which is the most far from collider pivot.
        virtual bool isCollidingWith(Collider *collider) = 0; //Returns true if collider is touching other collider.
};