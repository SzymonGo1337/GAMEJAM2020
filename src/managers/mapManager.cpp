#include "mapManager.hpp"
#include <stdexcept>

MapManager::MapManager() {

}

int MapManager::addEntity(std::initializer_list<std::pair<sf::Uint8, Entity*>> entities) {

}

bool MapManager::addEntity(sf::Uint8 id, Entity *entity) {

}

Map* MapManager::createFromFile(const char* fileName) const {
	sf::Image mapFile;
	if(!mapFile.loadFromFile(fileName)){
		throw std::ios_base::failure("Can't load file");
	}
	sf::Vector2u size = mapFile.getSize();
	const sf::Uint8 *imagePixels = mapFile.getPixelsPtr(); //RGBA

	std::vector<Entity*> entitiesOnMap;
	Map *map = new Map(size.x, size.y);

	sf::Vector2u spawnPoint;
	for(int y = 0 ; y < size.y ; y++){
		for(int x = 0 ; x < size.x ; x++){
			//RGBA
			const sf::Uint8 *pixel = imagePixels + ((y*size.x + x) * 4);
			map->mapGrid[y*size.x + x] = pixel[0];
			if(pixel[1] == 255){
				spawnPoint.x = x;
				spawnPoint.y = y;
			} else if(pixel[1] != 0) {
				if( entities.count(pixel[1]) ){
					//Add entity clone to entitiesOnMap
					//entitiesOnMap.push_back( entities.at(pixel[1])-> )
				}
			}

		}
	}

	map->init();
	return map;
}

// ===============================================
// ===================== Map =====================
// ===============================================

Map::Map(unsigned int pWidth, unsigned int pHeight) : width(pWidth), height(pHeight) {}

void Map::init() {

}

int Map::pos(unsigned int x, unsigned int y) const {
	return y*width + x;
}

int Map::blockAt(unsigned int x, unsigned int y) const {
	return mapGrid[pos(x, y)];
}

bool Map::collisionAt(unsigned int x, unsigned int y)  const {
	return blockAt(x, y)>>8;
}

const Entity* Map::getEntities() const {
	return entities;
}

unsigned int Map::getEntitiesCount() const {
	return entitiesCount;
}

int Map::getWdith() const {
	return width;
}

int Map::getHeight() const {
	return height;
}

sf::Vector2u Map::getSpawnPoint() const{
	return spawnPoint;
}