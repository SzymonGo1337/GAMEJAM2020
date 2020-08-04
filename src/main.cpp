#include <SFML/Graphics.hpp>
#include "components/particleSystem.hpp"
#include "components/colorGradient.hpp"
#include "util.hpp"

#include <SFML/OpenGL.hpp>

#include <string>
#include <sstream>

std::string str(const float &v){
	return std::to_string(v);
}

void limitUp(float &var, float max){
	while (var > max){
		var -= max;
	}
}
void limitDown(float &var, float min){
	while (var < min){
		var += min;
	}
}

std::string toStr(const sf::Color &c){
	std::stringstream ss;
	ss << c;
	return ss.str();
}

int main(){

	sf::RenderWindow window(sf::VideoMode(1500, 843), "SFML works!");

	sf::Clock clock;

	sf::Font font;
	if(!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf")){
		std::cerr << "font err" << std::endl;
		return 1;
	}

	sf::Text debugText;
	debugText.setFont(font);
	debugText.setColor(sf::Color::White);
	debugText.setPosition(10, 10);
	debugText.setCharacterSize(16);

	ParticleSystem pSys(5000);
	pSys.emitterPosition = sf::Vector2f(1500/2, 843/2);
	pSys.emissionRate = 100;
	pSys.emissionAngle = 20;
	pSys.emitterRotation = 0;
	pSys.particleLifeTime = {4.f, 6.f};
	pSys.particleColor = ColorGradient{
		{0.00f, sf::Color::White},
		{0.26f, sf::Color::Red},
		{0.50f, sf::Color::Blue},
		{0.75f, sf::Color::Green},
		{0.87f, sf::Color(255,255,0, 128)},
		{1.00f, sf::Color(255,0,0,0)}
	};

	pSys.debugDraw = true;

	std::cout << pSys.particleColor.evaluate(0.1f) << std::endl; //todo: fixme

	sf::RectangleShape test0(sf::Vector2f(100, 100));
	test0.setOrigin(50,50);
	test0.setPosition(725,300);
	
	sf::RectangleShape test1(sf::Vector2f(100, 100));
	test1.setOrigin(50,50);
	test1.setPosition(75,300);


	float t = 0;
	float duration = 10;

	ColorGradient gradient0 {
		sf::Color(255,0,0),
		sf::Color(255,255,0),
		sf::Color(0,255,0),
		sf::Color(0,255,255),
		sf::Color(0,0,255),
		sf::Color(255,0,255),
		sf::Color(255,0,0)
	};

	ColorGradient gradient1;

	//  0          0.5            0.8          1
	// red -> green | white -> dark gray ----- .
	gradient1.addKey(0.5f, sf::Color(0, 255, 0));
	gradient1.addKey(0.8f, sf::Color(50, 50, 50));
	gradient1.addKey(0.5f, sf::Color(255, 255, 255));
	gradient1.addKey(0.0f, sf::Color(255, 0, 0));

	glPointSize(2.f);
	
	//window.setFramerateLimit(2);
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::MouseButtonPressed){
				pSys.debugDraw = !pSys.debugDraw;
			}
			if (event.type == sf::Event::MouseMoved){
				float y = event.mouseMove.y;
				pSys.emissionRate = 2000 * (y / window.getSize().y);
				//pSys.emitterPosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
			}
		}

		sf::Time dt = clock.restart();
		float deltaTime = dt.asSeconds();

		t += deltaTime/duration;
		pSys.emitterRotation += 20 * deltaTime;

		limitUp(t, 1);
		limitUp(pSys.emitterRotation, 360);

		test0.setFillColor( gradient0.evaluate(t) );
		test1.setFillColor( gradient1.evaluate(t) );

		
		pSys.update(deltaTime);


		debugText.setString(
			  "ps.r: " + str(pSys.emitterRotation) 
			+ "; speed: MinMax{"+ str(pSys.particleSpeed.getMin()) + ";" + str(pSys.particleSpeed.getMax())+"}"
			+ "\nemissionRate: " + str(pSys.emissionRate) 
			+ "\nemissionTime: " + str(pSys.getEmissionTimeElapsed()) + " / " + str(pSys.emissionTime)
			+ "\nusedParticles: " + str(pSys.getUsedParticlesCount()) + " / " + str(pSys.getParticlesCount())
				+ " (free: " + str(pSys.getFreeParticlesCount())+")"
			);

		window.clear();

		// window.draw(test0);
		// window.draw(test1);
		window.draw(pSys);


		window.draw(debugText);
		window.display();
	}

	return 0;
}