#include "player.hpp"

Player::Player() {

	shape.setSize(sf::Vector2f(30, 30));

	shape.setFillColor(sf::Color::Red);
	
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	
}

Player::~Player() {

}

Entity *Player::clone() const {

    Player *p = new Player();
    p->shape = this->shape;

    return p;
		
}

void Player::update(const float &dt) {
	
	//TODO: keys binding
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) shape.move(0, -150*dt);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) shape.move(0, 150*dt);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) shape.move(-150*dt, 0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) shape.move(150*dt, 0);	

}