#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
protected:
	sf::Uint8 additionalData;
	sf::RectangleShape shape;

public:


	Entity() {};
	virtual ~Entity() {};

	sf::RectangleShape &getShape() { return shape; }


	virtual Entity* clone(sf::Uint8 additionalData = 0) const = 0;


	virtual void update() = 0;


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
		target.draw(shape, states);
	}

	sf::Uint8 getAdditionalData();
};