#pragma once

#include <SFML/Graphics.hpp>

class App{
private:
	sf::RenderWindow *window;
	sf::Event event;

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