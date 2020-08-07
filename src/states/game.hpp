#pragma once

#include "state.hpp"
#include "../entity/player.hpp"
#include "../entity/entity.hpp"
#include "../effects/text.hpp"
#include "../managers/mapManager.hpp"
#include "../components/particleSystem.hpp"

class GameState : public State {
private:
	Entity* player = new Player;

	Text *text;

	Camera camera;

	Map *map;

	ParticleSystem backgroundParticleA;
	ParticleSystem backgroundParticleB;
	sf::Texture *particleTexture;

public:
	GameState(Data *data);
	~GameState();

	void updateEvents(sf::Event &event);

	void update();

	void render();
};