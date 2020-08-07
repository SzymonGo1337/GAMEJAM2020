#pragma once

#include <map>

#include <SFML/Graphics/Transformable.hpp>

#include "../entity/entity.hpp"

class Map;

/*
Map construction: RGB image file.
 * Red: 
    0-127 - no collision (8th bit is collision mask)
	128-255 - collision

 * Green: 
   * Entity ID
   * 255 - Player
   * 0 - Nothing

 * Blue:
   * Element custom data (eg. door/key id)
   * 0 - No data
*/
class MapManager {
private:
	std::map<sf::Uint8, Entity*> entities;

public:
	MapManager();

	int addEntity(std::initializer_list<std::pair<sf::Uint8, Entity*>> entities);
	bool addEntity(sf::Uint8 id, Entity *entity);

	/**
	 * Read map data from file creates Map instance using entity data
	 * @returns new Map 
	 * @throw std::ios_base::failure on IO exception
	 */
	Map* createFromFile(const char* fileName) const;
	
};

class Map : public sf::Drawable, public sf::Transformable {
private:
	friend class MapManager;

	unsigned int width;
	unsigned int height;

	unsigned int entitiesCount;	

	sf::Uint8 *mapGrid;
	Entity **entities;

	sf::RenderTexture texture;

	sf::Vector2u spawnPoint;

	Map(unsigned int width, unsigned int height);

	void init();

protected:
	int pos(unsigned int x, unsigned int y) const;

public:
	/**
	 * @return block id or 0 if there is nothing 
	 */
	int blockAt(unsigned int x, unsigned int y) const;
	bool collisionAt(unsigned int x, unsigned int y) const;

	const Entity** getEntities() const;
	unsigned int getEntitiesCount() const;


	int getWdith() const;
	int getHeight() const;

	sf::Vector2u getSpawnPoint() const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
