#include "gui.hpp"

int main(){
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");

	Slider s1(20.0f, 20.0f, "point.png", "slider.png");

	while (window->isOpen()){
		sf::Event event;
		while (window->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();

		s1.draw(*window);

		window->display();
	}

	return 0;
}