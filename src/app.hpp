#pragma once

#include <SFML/Graphics.hpp>

class App{
private:
	sf::RenderWindow *window;
	sf::Event event;

public:
	App();
	~App();

	void run();
	void updateEvents();
	void update();
	void render();
};