#pragma once

#include <SFML/Graphics.hpp>

#include "animationCurve.hpp"
#include "../util.hpp"


/*
Emmiter rotation and angle:

     ^ Y axis
     |
     |
\  _____  /
 \/     \/_
  \  b  /  \
   \   / \  \
    \ / a |  |
-----o-------|----> X axis
      \      |
       \ b  / 
        \__/
         \


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

public: 
    sf::Vector2f emitterPosition;
	/** degree */
	float emitterRotation = 0;
	/** degree */
	float emissionAngle = 45;
	/** use '-1' for infinite */
	float emissionTime = -1;
	
	MinMax particleLifeTime;
	MinMax particleSpeed;


	AnimationCurveFunction animationCurve;

    ParticleSystem(unsigned int count);

    void setEmitter(sf::Vector2f position);

    void update(float deltaTime);


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

   
    void resetParticle(std::size_t index);

};