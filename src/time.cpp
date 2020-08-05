#include "time.hpp"

sf::Clock clock;
sf::Clock fromStart;

int framesInSecond;
int framesPerSecond;
long lastFpsTime;
sf::Time timeElapsed;
sf::Time timeDelta;

float deltaAsSeconds;

void GameTime::init(){
	clock.restart();
	fromStart.restart();
	framesInSecond = 0;
	framesPerSecond = 0;
	lastFpsTime = 0;
}

void GameTime::update(){
	timeDelta = clock.restart();
	timeElapsed = fromStart.getElapsedTime();
	deltaAsSeconds = timeDelta.asSeconds();

	int elt = elapsedMs();

	++framesInSecond;
	if(lastFpsTime + 1000 < elt){
		lastFpsTime = elt;
		framesPerSecond = framesInSecond;
		framesInSecond = 0;
	} 
}

float GameTime::delta(){
    return deltaAsSeconds;
}

float GameTime::dt(){
    return deltaAsSeconds;
}

float GameTime::elapsed(){
	return timeElapsed.asSeconds();
}
int  GameTime::elapsedMs(){
	return timeElapsed.asMilliseconds();
}

int  GameTime::FPS(){
	return framesPerSecond;
}