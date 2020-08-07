#include"playerCollisionDetector.hpp"
#include<math.h>

void PlayerCollisionDetector::checkCollisionsAndFixPosition(){
    float halfWidth = playerWidth * 0.5f;
    float halfHeight = playerHeight * 0.5f;
    sf::Vector2f centerPosition = sf::Vector2f(position.x + halfWidth, position.y + halfHeight);
    sf::Vector2i tilePosition = sf::Vector2i((int)floor(centerPosition.x), (int)floor(centerPosition.y));

    if (centerPosition.x + halfWidth > tilePosition.x + 1){ //Check right side
        velocity.x = 0;
        position.x = tilePosition.x + 1 - halfWidth;
    }
    else if (centerPosition.x - halfWidth < tilePosition.x){ //Check left side
        velocity.x = 0;
        position.x = tilePosition.x + halfWidth;
    }

    if (centerPosition.y + halfHeight > tilePosition.y + 1){ //Check bottom side
        velocity.y = 0;
        position.y = tilePosition.y + 1 - halfHeight;
    }
    else if (centerPosition.y - halfHeight < tilePosition.y){ //Check top side
        velocity.y = 0;
        position.y = tilePosition.y + halfHeight;
    }
}