#pragma once

#include <SFML/Graphics.hpp>
#include "managers/stateManager.hpp"
#include "states/game.hpp"

#include "config.hpp"

class App {
private:
	sf::RenderWindow *window;
	sf::Event event;

	StateManager sMan;

	Config cfg;
	
	sf::Image icon;
public:
	App();
	~App();

	void run();
	void updateEvents();
	void update();
	void render();
	
	void setIcon(const std::string &iconImage);
};