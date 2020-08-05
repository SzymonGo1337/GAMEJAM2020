#pragma once

#include "state.hpp"
#include "../entity/player.hpp"
#include "../entity/entity.hpp"

class GameState : public State {
private:
	Entity* player = new Player;
public:
	GameState() {

	}

	~GameState() {
		
	}

	void update() {
		//printf("works\n");
		player->update();
	}

	void render(sf::RenderWindow *window) {
		player->render(window);
	}
};
