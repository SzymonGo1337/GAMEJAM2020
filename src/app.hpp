#pragma once

#include <SFML/Graphics.hpp>
#include "managers/stateManager.hpp"
#include "states/menu.hpp"

class App {
private:
	sf::RenderWindow *window;
	sf::Event event;

	StateManager sMan;

	sf::Image icon;
public:
	App();
	~App();

	void run();
	void updateEvents();
	void update();
	void render();
	
	void setIcon(std::string iconImage);
};