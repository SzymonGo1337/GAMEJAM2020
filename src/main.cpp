#include "physics.hpp"

int main(){
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(20.0f, 20.0f));
	rect.setPosition(50.0f, 50.0f);
	rect.setFillColor(sf::Color::Cyan);

	Box b1(100.0f, 100.0f, sf::Vector2f(20.0f, 20.0f), sf::Color::Cyan);

	while (window->isOpen()){
		sf::Event event;
		while (window->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();

		//window->draw(rect);
		b1.physics(0.0f, 0.1f, 1.0f);
		b1.draw(*window);

		window->display();
	}

	return 0;
}