#pragma once

#include <SFML/System/Vector2.hpp>

class Collider{
    public:
        sf::Vector2f position;
        sf::Vector2f scale; //doesn't work :V
        float rotation; //also doesn't work :V (I have no time to implement it yet, so lmao)
    protected:
        virtual ~Collider() {}; //Yes only reason that I made this virtual destructor is because I wasn't be able to compile my code without it.
    public:
        virtual float getColliderMaxSizeFromPivot() = 0; //Returns point in collider, which is the most far from collider pivot.
};