#include "physics.hpp"

Box::Box(float x, float y, sf::Vector2f size, sf::Color color) {
	rect.setSize(size);
	rect.setPosition(x, y);
	rect.setFillColor(color);
}

void Box::draw(sf::RenderTarget &target) {
    target.draw(rect);
}

void Box::physics(float x, float y, float speed) {
    rect.setPosition(rect.getPosition().x + x * speed, rect.getPosition().y - y * speed);
}