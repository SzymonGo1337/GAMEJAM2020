#pragma once

#include <SFML/Graphics.hpp>

class Entity {
protected:

public:
	Entity() {};
	~Entity() {};
	virtual void update() = 0;
	virtual void render(sf::RenderWindow *window) = 0;
};