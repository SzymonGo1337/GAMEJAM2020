#include "mapManager.hpp"
#include <stdexcept>

MapManager::MapManager() {

}

int MapManager::addEntity(std::initializer_list<std::pair<sf::Uint8, Entity*>> entities) {
	
	int insertedValues = 0;

	std::initializer_list<std::pair<sf::Uint8, Entity*>>::iterator it;
	for(it = entities.begin() ; it < entities.end() ; it++){
		std::pair<std::map<sf::Uint8, Entity*>::iterator, bool> ret;
		ret = this->entities.insert(*it);
		insertedValues += (int)ret.second;
	}

	return insertedValues;
}

bool MapManager::addEntity(sf::Uint8 id, Entity *entity) {
	
	std::pair<std::map<sf::Uint8, Entity*>::iterator, bool> ret;
	ret = entities.insert(std::pair<sf::Uint8, Entity*>(id, entity));

	return ret.second;
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
	map->spawnPoint = spawnPoint;
	map->init();
	return map;
}

// ===============================================
// ===================== Map =====================
// ===============================================

Map::Map(unsigned int pWidth, unsigned int pHeight) : 
	width(pWidth),
	height(pHeight),
	vertex(sf::PrimitiveType::Quads, 4)
{
	vertex[0].position = sf::Vector2f(0     , 0       );
	vertex[1].position = sf::Vector2f(pWidth, 0       );
	vertex[2].position = sf::Vector2f(pWidth, pHeight );
	vertex[3].position = sf::Vector2f(0     , pHeight );

	vertex[0].color = vertex[1].color = vertex[2].color = vertex[3].color = sf::Color::White;
}

Map::~Map() {
	for(size_t i = 0 ; i < entitiesCount ; i++){
		delete entities[i];
	}
	delete[] entities;
	delete[] mapGrid;
	delete[] texture;
}

#include <iostream>
/*
TODO: Move him to other place (somewhere where he can live until we make last bug fixes before deadline)

                  /\ .---._      +------------------------------+
               /\/.-. /\ /\/\   <  Map rendering errors go brrr |
             //\\oo //\\/\\\\    +------------------------------+
            //  /"/`---\\ \\"`-._
        _.-'"           "`-.`-.
*/
void Map::init() { 

	const unsigned int cellPixelSize = 8;
	const unsigned int cellBorderWidth = 1;
	const unsigned int mapWidth = this->width;
	const unsigned int mapHeight = this->height;

	const sf::Uint32 background = 0x00000000; 
	const sf::Uint32 decoration = 0xFFFFFFFF;
	const sf::Uint32 block = 0xFF000000;

	sf::Uint32 *pixels = new sf::Uint32[ width * cellPixelSize * height * cellPixelSize];

	//Fills cellPixelSize * cellPixelSize at specific (x,y)*cellPixelSize

	auto fill = [&](size_t x, size_t y, size_t w, size_t h, sf::Uint32 color){
		for(size_t i = 0 ; i < h ; i++){
			for(size_t j = 0 ; j < w ; j++){
				pixels[(y + i)*mapWidth*cellPixelSize + x + j] = color;
			}	
		}
	};

	for(size_t y = 0 ; y < height ; y++){
		for(size_t x = 0 ; x < width ; x++){
			std::cout << collisionAt(x,y) << " ";
			if(!collisionAt(x,y)){

				fill(x*cellPixelSize, y*cellPixelSize, cellPixelSize, cellPixelSize, background );
			}
			else { //draw white lines;
				fill(x*cellPixelSize, y*cellPixelSize, cellPixelSize, cellPixelSize, block);
				if(x > 0 && !collisionAt(x-1, y)){
					fill(x * cellPixelSize, y * cellPixelSize,
						cellBorderWidth, cellPixelSize,
						decoration);
				}
				if(x+1 < width && !collisionAt(x+1, y)){
					fill(x * cellPixelSize + cellPixelSize - cellBorderWidth, y * cellPixelSize,
						cellBorderWidth, cellPixelSize,
						decoration);
				}
				if(y > 0 && !collisionAt(x, y-1)){
					fill(x * cellPixelSize, y * cellPixelSize,
						cellPixelSize, cellBorderWidth,
						decoration);
				}
				if(y+1 < height && !collisionAt(x, y+1)){
					fill(x * cellPixelSize, y * cellPixelSize + cellPixelSize - cellBorderWidth,
						cellPixelSize, cellBorderWidth,
						decoration);
				}
				if(x>0 && y>0 && !collisionAt(x-1, y-1)){
					fill(x * cellPixelSize, y * cellPixelSize,
						cellBorderWidth, cellBorderWidth,
						decoration);
				}
				if(x+1<width && y+1<height && !collisionAt(x+1, y+1)){
					fill((x+1) * cellPixelSize - cellBorderWidth, (y+1) * cellPixelSize - cellBorderWidth,
						cellBorderWidth, cellBorderWidth,
						decoration);
				}
				if(x>0 && y+1<height && !collisionAt(x-1, y+1)){
					fill(x * cellPixelSize, (y+1) * cellPixelSize - cellBorderWidth,
						cellBorderWidth, cellBorderWidth,
						decoration);
				}
				if(x+1<width && y>0 && !collisionAt(x+1, y-1)){
					fill((x+1) * cellPixelSize - cellBorderWidth, y * cellPixelSize,
						cellBorderWidth, cellBorderWidth,
						decoration);
				}
			}
		}
		std::cout << std::endl;
	}

	sf::Image img;
	img.create(width * cellPixelSize, height * cellPixelSize, (sf::Uint8*)pixels);

	texture = new sf::Texture();
	if(texture->loadFromImage(img)){
		//texture->update((sf::Uint8*)pixels);
		std::cout << "map ready!" << std::endl;
	}
	
	vertex[0].texCoords = sf::Vector2f(0                    , 0);
	vertex[1].texCoords = sf::Vector2f(width * cellPixelSize, 0);
	vertex[2].texCoords = sf::Vector2f(width * cellPixelSize, height * cellPixelSize);
	vertex[3].texCoords = sf::Vector2f(0                    , height * cellPixelSize);
	
	delete[] pixels;
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

int Map::getWidth() const {
	return width;
}

int Map::getHeight() const {
	return height;
}

sf::Vector2u Map::getSpawnPoint() const{
	return spawnPoint;
}
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	states.texture = texture;

	target.draw(vertex, states);
}