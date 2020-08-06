#include "app.hpp"

App::App() {

	cfg.load("config");

	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "placeholder name");

	//setting up window
	try {

		window->setFramerateLimit(cfg.getValue("FPS_LIMIT"));
		window->setVerticalSyncEnabled(cfg.getValue("VSYNC"));

	} catch(const std::exception &e) {

		fprintf(stderr, "%s\n", e.what());
	}

	//update data
	data.window = window;
	
	
	//setting state
	sMan.setState(new GameState(&data));

}

App::~App() {
	
	delete window;
}

void App::run() {

	//main loop
	while(window->isOpen()) {

		clock.restart();


		updateEvents();
		update();
		render();



		//printf("%f\n", deltaTime);
		//printf("%d\n", fps);

		//update time
		deltaTime = clock.getElapsedTime().asSeconds();
		fps = 1 / deltaTime;
	}
}

void App::updateEvents() {

	while(window->pollEvent(event)) {

		if(event.type == sf::Event::Closed)
			window->close();

		sMan.getState()->updateEvents(event);

	}
}

void App::update() {

	sMan.getState()->update(deltaTime);

}

void App::render() {

	//window
	window->clear();

	sMan.getState()->render();

	window->display();
}

//set icon
void App::setIcon(const std::string &iconImage) {

	icon.loadFromFile(iconImage);
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	
}