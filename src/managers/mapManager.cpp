#include "mapManager.hpp"
#include <stdexcept>

MapManager::MapManager() {

}

int MapManager::addEntity(std::initializer_list<std::pair<sf::Uint8, Entity*>> entities) {
	return 0;
}

bool MapManager::addEntity(sf::Uint8 id, Entity *entity) {
	return false;
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
	map->mapGrid = new sf::Uint8[size.x * size.y];

	sf::Vector2u spawnPoint;
	for(size_t y = 0 ; y < size.y ; y++){
		for(size_t x = 0 ; x < size.x ; x++){
			//RGBA
			//R - collision; G - Entity; B - Data
			const sf::Uint8 *pixel = imagePixels + ((y*size.x + x) * 4);

			map->mapGrid[y*size.x + x] = pixel[0]; //colision

			if(pixel[1] == 255) { // is player
				spawnPoint.x = x;
				spawnPoint.y = y;
			}
			else if(pixel[1] != 0) { // is entity
				if( entities.count(pixel[1]) ){ // entity is defined
					// copy entity
					// pixel[2] - data
					Entity *copy = entities.at(pixel[1])->clone(pixel[2]);

					copy->getShape().setPosition(x, y);


					
					entitiesOnMap.push_back( copy );
				}
			}

		}
	}

	map->entitiesCount = entitiesOnMap.size();
	map->entities = new Entity*[entitiesOnMap.size()];
	for(size_t i = 0 ; i < entitiesOnMap.size() ; i++){
		map->entities[i] = entitiesOnMap[i];
	}

	map->init();
	return map;
}

// ===============================================
// ===================== Map =====================
// ===============================================

Map::Map(unsigned int pWidth, unsigned int pHeight) : width(pWidth), height(pHeight) {}

Map::~Map() {
	//TODO pointers
}

void Map::init() {

}

int Map::pos(unsigned int x, unsigned int y) const {
	return y*width + x;
}

int Map::blockAt(unsigned int x, unsigned int y) const {
	return mapGrid[pos(x, y)];
}

bool Map::collisionAt(unsigned int x, unsigned int y)  const {
	return blockAt(x, y)>>7;
}

Entity** Map::getEntities() const {
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
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//TODO
}