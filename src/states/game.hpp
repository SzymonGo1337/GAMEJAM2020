#pragma once

#include "state.hpp"
#include "../entity/player.hpp"
#include "../entity/entity.hpp"
#include "../effects/text.hpp"

class GameState : public State {
private:
	Entity* player = new Player;

	Text *text;

	Camera camera;

public:
	GameState(Data *data);
	~GameState();

	void updateEvents(sf::Event &event);

	void update();

	void render();
};
