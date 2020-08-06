#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "managers/stateManager.hpp"
#include "states/game.hpp"


#include "config.hpp"

class App {
private:
	sf::RenderWindow *window;
	sf::Event event;

	StateManager sMan;

	Config cfg;
	
	Data data;

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