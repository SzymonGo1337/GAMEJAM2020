#include "gui.hpp"

void test() {
	std::cout << "isClicked" << std::endl;
}

int main(){
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works!");

	Button btn1(50.0f, 50.0f, "normal.png", "pressed.png");

	while (window->isOpen()){
		sf::Event event;
		while (window->pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();

		btn1.draw(*window);
		btn1.clicked(*window, test);

		window->display();
	}

	return 0;
}