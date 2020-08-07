#include "player.hpp"

#include "../time.hpp"

Player::Player() {

	shape.setSize(sf::Vector2f(30, 30));

	shape.setFillColor(sf::Color::Red);
	
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	
}

Player::~Player() {

}

Entity *Player::clone(sf::Uint8 additionalData = 0) const {

    Player *p = new Player();
    p->shape = this->shape;

	if(additionalData != 0)
		p->additionalData = additionalData;
	else 
		p->additionalData = this->additionalData;

    return p;
		
}

void Player::update() {
	
	//TODO: keys binding
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) shape.move(0, -150 * GameTime::dt());
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) shape.move(0,  150 * GameTime::dt());
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) shape.move(-150 * GameTime::dt(),  0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) shape.move( 150 * GameTime::dt(),  0);	

}