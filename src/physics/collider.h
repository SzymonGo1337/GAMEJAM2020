#pragma once

#include "physics.hpp"

class Collider{
    public:
        sf::Vector2f position;
        sf::Vector2f scale;
        float rotation;
    public:
        Collider(sf::Vector2f position); //Creates Collider with {1, 1} scale and rotation of 0.
        Collider(sf::Vector2f position, sf::Vector2f scale); //Creates Collider with rotation of 0.
        Collider(sf::Vector2f position, sf::Vector2f scale, float rotation);
        virtual float getColliderMaxSizeFromPivot() = 0; //Returns point in collider, which is the most far from collider pivot.
        virtual bool isCollidingWith(Collider *collider) = 0; //Returns true if collider is touching other collider.
};