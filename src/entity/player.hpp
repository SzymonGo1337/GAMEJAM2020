#pragma once

#include "../components/animation.hpp"
#include "../physics/playerCollisionDetector.hpp"
#include "../states/game.hpp"

class Player : public Entity {
private:
	PlayerCollisionDetector collisionDetector;
public:
	Player(GameState *state);
	virtual ~Player();

	Entity *clone(sf::Uint8 additionalData = 0) const override;

	void update() override;
};