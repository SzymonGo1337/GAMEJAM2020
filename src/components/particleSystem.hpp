#pragma once

#include <SFML/Graphics.hpp>

#include "animationCurve.hpp"
#include "colorGradient.hpp"
#include "../util.hpp"

enum ParticleSystemShape {
	POINT = 0,
	CIRCLE = 1,
	RECTANGLE = 2,
};

/*
Emmiter rotation and angle:

    Y axis
     ^ 
     |    /
     |   /_
     |  /  \
     | /  b \
     |/      |
-----o----+--+----> X axis
    / \ a |  |
   /   \_/  / 
  /  b  \__/
 /\_____/\
/         \ 


a - rotation
b - angle * 0.5
*/
class ParticleSystem : public sf::Drawable, public sf::Transformable {
private:
	struct Particle {
        sf::Vector2f velocity;
        float lifetime;
    };

    std::vector<Particle> particles;
    sf::VertexArray vertices;

	sf::VertexArray debugArr;

	int unusedParticles;
	int lastEmittedParticleIndex = 0;
	float particlesToEmit = 0;

	float currentEmissionTime = 0;

public: 
	bool debugDraw = false;

    sf::Vector2f emitterPosition;
	/** degrees */
	float emitterRotation = 0;
	/** degrees */
	float emissionAngle = 45;
	/** use '-1' for infinite */
	float emissionTime = -1;

	/** Number of particles to emit every second */
	int emissionRate = 100;
	
	MinMax particleLifeTime;
	MinMax particleSpeed;

	ColorGradient particleColor;
	AnimationCurveFunction colorAnimationCurve;

    ParticleSystem(unsigned int count);

    void update(float deltaTime);

	/**
	 * @returns true when emitter was emiting for 'emissionTime` seconds.
	 */
	bool finished();

	void resetEmitter();

	float getEmissionTimeElapsed();

	/**
	 * @returns number of particles currently not used in render 
	 */
	int getFreeParticlesCount();

	/**
	 * @returns number of particles currently used in render 
	 */
	int getUsedParticlesCount();

	int getParticlesCount();

private:

	void updateDebug(float deltaTime);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
   
    void emitParticle(std::size_t index);

};
