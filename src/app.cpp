#include "app.hpp"

App::App() {

	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "placeholder name");
	window->setFramerateLimit(60);
}

App::~App() {

	delete window;
}

void App::run() {

	while(window->isOpen()) {

		updateEvents();
		update();
		render();

	}
}

void App::updateEvents() {

	while(window->pollEvent(event)) {

		switch(event.type) {
			case sf::Event::Closed: window->close(); break;
		}

	}
}

void App::update() {

	sMan.getState()->update();

}

void App::render() {

	window->clear();

	sMan.getState()->render();

	window->display();
}

void App::setIcon(std::string iconImage) {

	icon.loadFromFile(iconImage);
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
}