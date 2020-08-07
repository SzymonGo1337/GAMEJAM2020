#include <iostream>

#include "player.hpp"
#include "../time.hpp"

Player::Player(GameState *state) : Entity(state) {

	shape.setSize(sf::Vector2f(50, 50));

	shape.setFillColor(sf::Color::Red);
	
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
	
	collisionDetector = PlayerCollisionDetector();
	collisionDetector.map = gameState->map;
	collisionDetector.playerWidth = getShape().getSize().x;
	collisionDetector.playerHeight = getShape().getSize().y;
}

Player::~Player() {

}

Entity *Player::clone(sf::Uint8 additionalData) const {

    Player *p = new Player(gameState);
    p->shape = sf::RectangleShape(this->shape);

	if(additionalData != 0)
		p->additionalData = additionalData;
	else 
		p->additionalData = this->additionalData;

    return p;
		
}

void Player::update() {
	const float speed = 10.f;
	const float drag = 2.f;
	//collisionDetector.velocity = sf::Vector2f(0, 0);
	sf::Vector2f inputAxis(0,0);
	inputAxis.y -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	inputAxis.y += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
	inputAxis.x -= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
	inputAxis.x += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	inputAxis = inputAxis * speed * GameTime::dt();
	setKey("input", tostr(inputAxis));

	sf::Vector2f velocity = collisionDetector.velocity;

	// sf::Vector2f velD = -velocity * drag * GameTime::dt();
	// float velEff = 1.f - GameTime::dt() * drag;

	// velocity += (velD + inputAxis) * velEff;

	velocity += inputAxis;
	velocity -= velocity * drag * GameTime::dt();

	collisionDetector.velocity = velocity;

	collisionDetector.position = shape.getPosition();
	collisionDetector.position += collisionDetector.velocity;
	collisionDetector.checkCollisionsAndFixPosition();

	//std::cout << collisionDetector.position << " ";
	//std::cout << shape.getPosition() << std::endl;

	shape.move(collisionDetector.position - shape.getPosition());

	//TODO: keys binding
	/*
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) shape.move(0, -150 * GameTime::dt());
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) shape.move(0,  150 * GameTime::dt());
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) shape.move(-150 * GameTime::dt(),  0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) shape.move( 150 * GameTime::dt(),  0);	
*/
}