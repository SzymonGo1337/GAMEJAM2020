#pragma once

#include "entity.hpp"
#include "../components/animation.hpp"
#include "../physics/physics.hpp"

class Player : public Entity {
private:
	PlayerCollisionDetector collisionDetector;
public:
	Player(GameState **state) : Entity(state) {};
	virtual ~Player();

	Entity *clone(sf::Uint8 additionalData = 0) const override;

	void update() override;
};