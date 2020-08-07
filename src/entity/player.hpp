#pragma once

#include "entity.hpp"
#include "../components/animation.hpp"

class Player : public Entity {
private:

public:
	Player();
	virtual ~Player();

	Entity *clone(sf::Uint8 additionalData = 0) const override;

	void update() override;
};