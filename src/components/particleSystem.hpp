#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "animationCurve.hpp"
#include "colorGradient.hpp"
#include "../util.hpp"


/*
Default shape as Point
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
class ParticleSystemShape {
public:
	float rotation;
	float angle;

	ParticleSystemShape() : rotation(0), angle(0) {}
	ParticleSystemShape(float pRotation, float pAngle) :
		rotation(pRotation), angle(pAngle) {}

	
	virtual sf::Vector2f getParticlePosition() const;
	virtual sf::Vector2f getParticleVelocity(const MinMax &speed) const;

	virtual void debugDraw(sf::VertexArray &arr, sf::Vector2f position) const;
};

class ParticleSystemShapeBox : public ParticleSystemShape {
public:
	sf::Vector2f size;

	ParticleSystemShapeBox() : ParticleSystemShape(), size(10,10) {}
	ParticleSystemShapeBox(sf::Vector2f pSize, float pRotation = 0.f, float pAngle = 0.f) :
		ParticleSystemShape(pRotation, pAngle), size(pSize) {}

	
	virtual sf::Vector2f getParticlePosition() const override;
	virtual sf::Vector2f getParticleVelocity(const MinMax &speed) const override;

	virtual void debugDraw(sf::VertexArray &arr, sf::Vector2f position) const override;
};

class ParticleSystem : public sf::Drawable, public sf::Transformable {
private:
	struct Particle {
		sf::Vector2f position;
        sf::Vector2f velocity;
        float lifetime;
		float rotation;
    };

    std::vector<Particle> particles;
    sf::VertexArray vertices;

	sf::VertexArray debugArr;

	int unusedParticles;
	int lastEmittedParticleIndex = 0;
	float particlesToEmit = 0;

	float currentEmissionTime = 0;

	sf::Vector2f textureSize;

public: 
	bool debugDraw = false;

    sf::Vector2f emitterPosition;
	ParticleSystemShape *emitterShape;

	/** use '-1' for infinite */
	float emissionTime = -1;

	/** Number of particles to emit every second */
	int emissionRate = 100;
	
	MinMax particleLifeTime;
	MinMax particleSpeed;

	sf::Vector2f particleGravity;

	float particleSize = 1;
	float particleRotationSpeed = 0;

	ColorGradient particleColorOverLifetime;
	AnimationCurveFunction colorAnimationCurve;
	AnimationCurveFunction scaleOverLifetime;
	AnimationCurveFunction rotationSpeedScaleOverLifetime;
	

	/** NULL for no texture */
	sf::Texture* texture;

    ParticleSystem(unsigned int count);

    void update(float deltaTime);

	/**
	 * @returns true when emitter was emiting for 'emissionTime` seconds.
	 */
	bool finished() const;

	void resetEmitter();

	float getEmissionTimeElapsed() const;

	/**
	 * @returns number of particles currently not used in render 
	 */
	int getFreeParticlesCount() const;

	/**
	 * @returns number of particles currently used in render 
	 */
	int getUsedParticlesCount() const;

	unsigned int getParticlesCount() const;

	void updateTextureSize(sf::Vector2f texSize);

private:

	void updateDebug(float deltaTime);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
   
    void emitParticle(std::size_t index);

	void setParticleColor(std::size_t index, const sf::Color &color);
};
