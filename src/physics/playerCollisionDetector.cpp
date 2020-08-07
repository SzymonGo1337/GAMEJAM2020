#include "playerCollisionDetector.hpp"
#include <math.h>
#include <iostream>

#include "../util.hpp"
#include "../time.hpp"

template <typename T>
sf::Vector2<T> mulAxes(const sf::Vector2<T> &a, const sf::Vector2<T> &b){
	return sf::Vector2<T>(a.x * b.x, a.y * b.y);
}

template <typename T>
sf::Vector2<T> divAxes(const sf::Vector2<T> &a, const sf::Vector2<T> &b){
	return sf::Vector2<T>(a.x / b.x, a.y / b.y);
}

typedef unsigned char uchar;

void PlayerCollisionDetector::checkCollisionsAndFixPosition(){
	sf::Vector2f halfSize = sf::Vector2f(playerWidth * 0.5f, playerHeight * 0.5f);
    sf::Vector2f gridSize = sf::Vector2f(playerWidth * 2, playerHeight * 2);
    sf::Vector2i tilePosition = sf::Vector2i(position.x / gridSize.x, position.y / gridSize.y);
    //std::cout << "curr: " << tilePosition.x << " " << tilePosition.y << " | " << map->getWidth() << " " << map->getHeight() << std::endl;

	setKey("tilePos", tostr(tilePosition));
	setKey("playerPos", tostr(position));
	setKey("velocity", tostr(velocity));

	sf::Vector2i nextTile(
		(position.x + sign(velocity.x) * 0.5f) / gridSize.x,
		(position.y + sign(velocity.y) * 0.5f) / gridSize.y );

	sf::Vector2f leftTop     = position + sf::Vector2f(-halfSize.x,  halfSize.y);
	sf::Vector2f rightTop    = position + sf::Vector2f( halfSize.x,  halfSize.y);
	sf::Vector2f rightBottom = position + sf::Vector2f( halfSize.x, -halfSize.y);
	sf::Vector2f leftBottom  = position + sf::Vector2f(-halfSize.x, -halfSize.y);

	sf::Vector2i leftTopI     = (sf::Vector2i) divAxes(leftTop,     gridSize);
	sf::Vector2i rightTopI    = (sf::Vector2i) divAxes(rightTop,    gridSize);
	sf::Vector2i rightBottomI = (sf::Vector2i) divAxes(rightBottom, gridSize);
	sf::Vector2i leftBottomI  = (sf::Vector2i) divAxes(leftBottom,  gridSize);
	
	uchar top    = 0b1;
	uchar bottom = 0b10;
	uchar left   = 0b100;
	uchar right  = 0b1000;
	

	uchar collMask = 0;
	collMask |= map->collisionAt(leftTopI)     * (left  | top);
	collMask |= map->collisionAt(rightTopI)    * (right | top);
	collMask |= map->collisionAt(rightBottomI) * (right | bottom);
	collMask |= map->collisionAt(leftBottomI)  * (left  | bottom);
	
	const float distCollMargin = sqrt(velocity.x * velocity.x + velocity.y * velocity.y)*GameTime::dt();;

	if(collMask){
		float distanceX = 0;
		float distanceY = 0;

		float gridPosX = 0;
		float gridPosY = 0;
		if(collMask & left){
			gridPosX = leftTopI.x * gridSize.x + gridSize.x;
			distanceX += abs(leftTop.x - gridPosX);
			if(collMask & top){
				gridPosY = leftTopI.y * gridSize.y;
				distanceY += abs(leftTop.y - gridPosY);
			}
			else if(collMask & bottom){
				gridPosY = leftBottomI.y * gridSize.y + gridSize.y;
				distanceY += abs(leftBottom.y - gridPosY);
			}
		}
		if(collMask & right){
			gridPosX = rightTopI.x * gridSize.x ;
			distanceX += abs(rightTop.x - gridPosX);

			if(collMask & top){
				gridPosY = rightTopI.y * gridSize.y;
				distanceY += abs(rightTop.y - gridPosY);
			}
			else if(collMask & bottom){
				gridPosY = rightBottomI.y * gridSize.y + gridSize.y;
				distanceY += abs(rightBottom.y - gridPosY);
			}
		}


		if(abs(distanceX - distanceY) < distCollMargin){
			position.x -= distanceX * sign(velocity.x);
			position.y -= distanceY * sign(velocity.y);
			velocity.x = 0;
			velocity.y = 0;
		}
		else if(distanceX < distanceY){
			position.x -= distanceX * sign(velocity.x);
			//position.x = gridPosX;
			velocity.x = 0;
		}
		else {
			//position.y = gridPosY;
			position.y -= distanceY * sign(velocity.y);
			velocity.y = 0;
		}
	}



	// if(map->collisionAt(tilePosition.x, tilePosition.y) && map->collisionAt(nextTile.x, nextTile.y)){
		
	// 	if(velocity.x != 0){
	// 		position.x = (tilePosition.x - sign(velocity.x)) * gridSize.x;
	// 		if(velocity.x > 0) position.x += gridSize.x;
	// 		velocity.x = 0;
	// 	}
	// 	if(velocity.y != 0){
	// 		position.y = (tilePosition.y - sign(velocity.y)) * gridSize.y;
	// 		if(velocity.y > 0) position.y += gridSize.y;
	// 		velocity.y = 0;
	// 	}			
	// }
	




	// setKey("Velocity", tostr(velocity) );
	// setKey("Pos", tostr(tilePosition) );

	// 
	// //std::cout << "NextTile: " << nextTile.x << " " << nextTile.y << std::endl;
	// if(velocity.x != 0 || velocity.y != 0){
	// 	setKey("NexTile", tostr(nextTile));
	// }


    // if (map->collisionAt(tilePosition.x, tilePosition.y)){
	// 	sf::Vector2f diff = position - (sf::Vector2f)tilePosition;
	// 	sf::Vector2f diffAbs = sf::Vector2f(abs(diff.x), abs(diff.y));
	// 	if(diffAbs.x > diffAbs.y) {
	// 		diff.x = sign(diff.x);
	// 		diff.y = 0;
	// 	}
	// 	else {
	// 		diff.x = 0;
	// 		diff.y = sign(diff.y);
	// 	}

	// 	//float mag = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	// 	float dot = velocity.x * diff.y + velocity.y * diff.x;

	// 	velocity.x = dot * diff.y;
	// 	velocity.y = dot * diff.x;
    // }

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