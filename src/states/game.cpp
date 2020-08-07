#include "game.hpp"

#include "../time.hpp"

GameState::GameState(Data *data) : State(data), backgroundParticleA(100), backgroundParticleB(100) {

	player = new Player(this);

	camera.follow(player);

	sf::Vector2f playerSize = player->getShape().getSize();
	particleTexture = new sf::Texture();
	if(!particleTexture->loadFromFile("res/particle1.png")){
		std::cout << "Can't load texture" << std::endl;
		particleTexture = NULL;
	}

	text = new Text("res/fonts/Ubuntu-Bold.ttf", "use W A S D to move", player->getShape().getPosition(), 18);
	text->setOffset(25, -45);

	MapManager mapManager;
	map = mapManager.createFromFile("res/testMap.png");
	std::cout << map->getSpawnPoint().x << " " << map->getSpawnPoint().y << std::endl;
	player->getShape().setPosition(((sf::Vector2f) map->getSpawnPoint()) * playerSize.x * 2.f + playerSize );

	map->setScale(playerSize.x*2, playerSize.x*2);

	sf::Vector2f mapSize = sf::Vector2f(map->getWidth() * playerSize.x * 2, map->getHeight() * playerSize.y * 2);

	backgroundParticleA.emitterPosition = sf::Vector2f(map->getWidth() * playerSize.x, (map->getHeight()+1) * playerSize.y);
	backgroundParticleA.emitterShape = new ParticleSystemShapeBox(mapSize, -90, 0);
	backgroundParticleA.particleSpeed = {5, 20};
	backgroundParticleA.particleLifeTime = {10, 20};
	backgroundParticleA.emissionTime = -1;
	backgroundParticleA.emissionRate = 5;
	backgroundParticleA.particleColorOverLifetime = {
		{0.00f, sf::Color(255,255,255,0)},
		{0.25f, sf::Color(255,255,255,150)},
		{0.75f, sf::Color(255,255,255,150)},
		{1.00f, sf::Color(255,255,255,0)},
	};
	backgroundParticleA.colorAnimationCurve = AnimationCurve::Linear;
	backgroundParticleA.particleRotationSpeed = 10;
	backgroundParticleA.particleSize = 5;
	backgroundParticleA.scaleOverLifetime = [](float t){return (-t*t-t)*4.f;};

	backgroundParticleB = backgroundParticleA;
	backgroundParticleB.texture = particleTexture;
	
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
	backgroundParticleA.update();
	backgroundParticleB.update();

	player->update();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)) camera.setShake(true, 500, 500);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) camera.setShake(true, 1000, 1000);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) camera.setShake(false, 0, 0);

	camera.update();
	text->follow(player, GameTime::dt(), 15);

	
}

void GameState::render() {

	data->window->setView(*camera.getView());


	data->window->draw(backgroundParticleA);
	data->window->draw(backgroundParticleB);
	data->window->draw(*map);

	data->window->draw(*player);
	data->window->draw(*text);

}