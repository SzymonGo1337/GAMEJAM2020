#include <SFML/Graphics.hpp>
#include "gui.hpp"

void test(float var) {
	std::cout << var << std::endl;
}

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	Slider s1(10.0f, 10.0f, sf::Color::Cyan, sf::Color::White);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		s1.clicked(window, test);
		s1.draw(window);

		window.display();
	}

	return 0;
}