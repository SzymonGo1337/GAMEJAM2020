#pragma once

#include <SFML/System/Vector2.hpp>
#include "../managers/mapManager.hpp"

class PlayerCollisionDetector{
    public:
        Map *map;
        sf::Vector2f position;
        float playerWidth;
        float playerHeight;

        sf::Vector2f velocity;
    public:
        void checkCollisionsAndFixPosition();
};