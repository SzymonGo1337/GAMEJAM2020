#include <SFML/Graphics.hpp>
#include "time.hpp"

int main(){

	sf::RenderWindow window(sf::VideoMode(1800, 1012), "SFML works!");

	GameTime::init();
	while (window.isOpen()){
		GameTime::update();

		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		

	}

	return 0;
}