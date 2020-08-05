#pragma once

#include "entity.hpp"

class Player : public Entity {
private:
	sf::RectangleShape shape;
public:
	Player();
	~Player();

	void update();
	void render(sf::RenderWindow *window);
};