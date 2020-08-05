#include "app.hpp"
#include "time.hpp"

App::App() {

	cfg.load("config");

	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "placeholder name");

	//setting up window
	window->setFramerateLimit(cfg.getValue("FPS_LIMIT"));
	window->setVerticalSyncEnabled(cfg.getValue("VSYNC"));

	//setting state to menu
	sMan.setState(new GameState());

}

App::~App() {
	
	delete window;
}

void App::run() {

	//main loop
	GameTime::init();
	while(window->isOpen()) {
		
		GameTime::update();
		updateEvents();
		update();
		render();

	}
}

void App::updateEvents() {

	while(window->pollEvent(event)) {

		if(event.type == sf::Event::Closed)
			window->close();

	}
}

void App::update() {

	sMan.getState()->update();

}

void App::render() {

	window->clear();

	sMan.getState()->render(window);

	window->display();
}

void App::setIcon(const std::string &iconImage) {

	icon.loadFromFile(iconImage);
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
}