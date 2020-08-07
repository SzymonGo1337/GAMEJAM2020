#include "playerCollisionDetector.hpp"
#include <math.h>
#include <iostream>

void PlayerCollisionDetector::checkCollisionsAndFixPosition(){
    sf::Vector2f gridSize = sf::Vector2f(playerWidth * 2, playerHeight * 2);
    sf::Vector2i tilePosition = sf::Vector2i(position.x / gridSize.x, position.y / gridSize.y);
    //std::cout << tilePosition.x << " " << tilePosition.y << std::endl;

    if (map->collisionAt(tilePosition.x, tilePosition.y)){
        
    }

    // float halfWidth = playerWidth * 0.5f;
    // float halfHeight = playerHeight * 0.5f;
    // sf::Vector2f centerPosition = sf::Vector2f(position.x + halfWidth, position.y + halfHeight);
    // sf::Vector2i tilePositionInMap = sf::Vector2i((int)floor(centerPosition.x / (playerWidth * 2)), 
    // (int)floor(centerPosition.y / (playerHeight * 2)));
    // sf::Vector2i tilePosition = //sf::Vector2i((int)floor(centerPosition.x * 0.5f), (int)floor(centerPosition.y * 0.5f));

    // if (centerPosition.x + halfWidth > tilePosition.x + 1){ //Check right side
    //     if (map->collisionAt(tilePositionInMap.x + 1, tilePositionInMap.y)){
    //         velocity.x = 0;
    //         position.x = tilePosition.x + 1 - halfWidth;
    //         std::cout<<"A"<<std::endl;
    //     }
    // }
    // else if (centerPosition.x - halfWidth < tilePosition.x){ //Check left side
    //     if (map->collisionAt(tilePositionInMap.x - 1, tilePositionInMap.y)){
    //         velocity.x = 0;
    //         position.x = tilePosition.x + halfWidth;
    //         std::cout<<"B"<<std::endl;
    //     }
    // }

    // if (centerPosition.y + halfHeight > tilePosition.y + 1){ //Check bottom side
    //     if (map->collisionAt(tilePositionInMap.x, tilePositionInMap.y + 1)){
    //         velocity.y = 0;
    //         position.y = tilePosition.y + 1 - halfHeight;
    //         std::cout<<"C"<<std::endl;
    //     }
    // }
    // else if (centerPosition.y - halfHeight < tilePosition.y){ //Check top side
    //     if (map->collisionAt(tilePositionInMap.x, tilePositionInMap.y - 1)){
    //         velocity.y = 0;
    //         position.y = tilePosition.y + halfHeight;
    //         std::cout<<"D"<<std::endl;
    //     }
    // }
}