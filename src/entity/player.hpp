#pragma once

#include "entity.hpp"
#include "../components/animation.hpp"

class Player : public Entity {
private:

public:
	Player();
	~Player();

	Entity *clone() const override;

	void update(const float &dt) override;
};