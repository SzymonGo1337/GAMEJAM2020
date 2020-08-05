#include <SFML/Graphics.hpp>
#include "components/particleSystem.hpp"
#include "components/colorGradient.hpp"
#include "util.hpp"

#include <SFML/OpenGL.hpp>

#include <string>
#include <sstream>
#include <cmath>

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

	sf::RenderWindow window(sf::VideoMode(1800, 1012), "SFML works!");

	sf::Clock clock;

	sf::Font font;
	if(!font.loadFromFile("/usr/share/fonts/truetype/ubuntu/UbuntuMono-R.ttf")){
		std::cerr << "font err" << std::endl;
		return 1;
	}

	sf::Text debugText;
	debugText.setFont(font);
	debugText.setFillColor(sf::Color::White);
	debugText.setPosition(10, 10);
	debugText.setCharacterSize(16);

	ParticleSystem pSys(3100);
	pSys.emitterPosition = sf::Vector2f(1800/2, 1012/2);
	pSys.emissionRate = 50;
	pSys.emitterShape = new ParticleSystemShapeBox(sf::Vector2f(500, 50));
	pSys.emitterShape->rotation = -45;
	pSys.emitterShape->angle = 0;
	pSys.particleLifeTime = {10.f, 15.f};
	pSys.emissionTime = -1; // -1 mean infinite emissionTime
	pSys.particleSpeed = {200, 300};
	pSys.particleGravity = sf::Vector2f(0,100);


	/*
	Other interesting curves:
		AnimationCurve::EaseInOut  
		AnimationCurve::EaseIn
		AnimationCurve::EaseOut
		AnimationCurve::Linear
		[](float f){return (float)pow(f, 2);}; //fast ending
		[](float f){return (float)pow(f, 0.5);}; //fast begining
		[](float f){return 1-(float)sqrt(1-f*f);}; //const acceleration of transition
		[](float f){return 1-(float)pow(1-sqrt(f),2);}; //const acceleration of transition (inverted)
		for f in [0;1] returned value must be in [0;1]
	*/
	pSys.colorAnimationCurve = AnimationCurve::EaseInOut;
	pSys.particleColorOverLifetime = ColorGradient{
		{0.00f, sf::Color(128,128,255,0)},
		{0.1f, sf::Color(128,128,255,255)},
		//{0.80f, sf::Color(128,128,255,255)},
		//{0.33f, sf::Color::Red},
		//{0.66f, sf::Color::Red},
		//{1.00f, sf::Color(128,128,255,0)},
		// {0.00f, sf::Color::White},
		// {0.26f, sf::Color::Red},
		// {0.50f, sf::Color::Blue},
		// {0.75f, sf::Color::Green},
		// {0.87f, sf::Color(255,255,0, 128)},
		// {1.00f, sf::Color(255,0,0,0)}
	};

	pSys.particleSize = 3;
	pSys.scaleOverLifetime = [](float f){return 1 - AnimationCurve::EaseOut(f);/*2-2*(-f*(f-2));*/};

	pSys.particleRotationSpeed = 180;
	pSys.rotationSpeedScaleOverLifetime = [](float f){return ((f<0.8f) ? (0.8f-f) : (0.f));};

	pSys.debugDraw = true;

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

	glPointSize(2.f); //size of particles
	
	//window.setFramerateLimit(2);
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::MouseButtonPressed){
				if(event.mouseButton.button == sf::Mouse::Button::Right)
					pSys.resetEmitter();
				else 
					pSys.debugDraw = !pSys.debugDraw;
				
			}
			if (event.type == sf::Event::MouseMoved){
				float y = event.mouseMove.y;
				float x = event.mouseMove.x;
				//pSys.emissionRate = 500 * (y / window.getSize().y);
				//pSys.emitterShape->angle = 270 * (x / window.getSize().x);
				//pSys.emitterPosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
			}
		}

		sf::Time dt = clock.restart();
		float deltaTime = dt.asSeconds();

		t += deltaTime/duration;
		//pSys.emitterShape->rotation += 20 * deltaTime;

		limitUp(t, 1);
		limitUp(pSys.emitterShape->rotation, 360);

		test0.setFillColor( gradient0.evaluate(t) );
		test1.setFillColor( gradient1.evaluate(t) );

		
		pSys.update(deltaTime);


		debugText.setString(
			  "FPS: " + str(1/deltaTime) + "; dt: "+ str(deltaTime)
			+ "\nrotation: " + str(pSys.emitterShape->rotation) 
			+ "; angle: " + str(pSys.emitterShape->angle)
			+ "\nspeed: MinMax{"+ str(pSys.particleSpeed.getMin()) + ";" + str(pSys.particleSpeed.getMax())+"}"
			+ "\nemissionRate: " + str(pSys.emissionRate) 
			+ "\nemissionTime: " + str(pSys.getEmissionTimeElapsed()) + " / " + str(pSys.emissionTime)
			+ "\nusedParticles: " + str(pSys.getUsedParticlesCount()) + " / " + str(pSys.getParticlesCount())
				+ " (free: " + str(pSys.getFreeParticlesCount())+")"
			);

		window.clear();

		// window.draw(test0); //Gradient test 1
		// window.draw(test1); //Gradient test 2
		window.draw(pSys);


		window.draw(debugText);
		window.display();
	}

	return 0;
}