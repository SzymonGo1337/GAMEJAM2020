#include "game.hpp"

#include "../time.hpp"

GameState::GameState(Data *data) : State(data) {

	camera.follow(player);

	text = new Text("res/fonts/Ubuntu-Bold.ttf", "use W A S D to move", player->getShape().getPosition(), 18);
	text->setOffset(25, -45);

}

GameState::~GameState() {

	delete player;
	
}

void GameState::updateEvents(sf::Event &event) {

	if(event.type == sf::Event::Resized) {

		float aspectRatio = (float)data->window->getSize().x / (float)data->window->getSize().y;

		camera.getView()->setSize(sf::Vector2f(720*aspectRatio, 720));

	}

}

void GameState::update() {

	player->update();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)) camera.setShake(true, 500, 500);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) camera.setShake(true, 1000, 1000);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) camera.setShake(false, 0, 0);

	camera.update();
	text->follow(player, GameTime::dt(), 15);

}

void GameState::render() {

	data->window->setView(*camera.getView());

	data->window->draw(*player);
	data->window->draw(*text);

}