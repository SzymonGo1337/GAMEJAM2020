#include "player.hpp"

Player::Player() {
	shape.setSize(sf::Vector2f(10, 10));
	shape.setFillColor(sf::Color::Red);
}

Player::~Player() {

}

void Player::update() {
	
	//TODO: keys binding
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) shape.move(0, -5);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) shape.move(0, 5);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) shape.move(-5, 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) shape.move(5, 0);

}
void Player::render(sf::RenderWindow *window) {
	window->draw(shape);
}