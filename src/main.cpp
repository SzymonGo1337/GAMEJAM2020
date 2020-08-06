#include <SFML/Graphics.hpp>
#include "time.hpp"

int main(){

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

	GameTime::init();
	while (window.isOpen()){
		GameTime::update();

		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		window.clear();

		window.display();
	}

	return 0;
}