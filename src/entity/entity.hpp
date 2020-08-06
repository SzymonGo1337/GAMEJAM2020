#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
protected:
	sf::RectangleShape shape;
public:
	Entity() {};
	virtual ~Entity() {};

	sf::RectangleShape &getShape() { return shape; }


	virtual Entity* clone() const = 0;


	virtual void update() = 0;


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
		target.draw(shape, states);
	}
};