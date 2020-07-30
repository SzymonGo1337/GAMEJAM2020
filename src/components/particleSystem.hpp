#pragma once


#include <SFML/Graphics.hpp>
#include <cmath>

#include "animationCurve.hpp"

class ParticleSystem : public sf::Drawable, public sf::Transformable {
private:
	struct Particle {
        sf::Vector2f velocity;
        float lifetime;
    };


    std::vector<Particle> particles;
    sf::VertexArray vertices;

public: 
    sf::Vector2f emitter;
	float lifeTime;
	float rotation;
	float angle;
	AnimationCurveFunction animationCurve;

    ParticleSystem(unsigned int count) :
		particles(count),
		vertices(sf::Points, count),
		lifeTime(3),
		emitter(0.f, 0.f)
	{
		animationCurve = AnimationCurve::EaseInOut;
    }

    void setEmitter(sf::Vector2f position) {
        emitter = position;
    }

    void update(float deltaTime) {
        for (std::size_t i = 0; i < particles.size(); ++i) {
            // update the particle lifetime
            Particle& p = particles[i];
            p.lifetime -= deltaTime;

            // if the particle is dead, respawn it
            if (p.lifetime <= 0)
                resetParticle(i);

            // update the position of the corresponding vertex
            vertices[i].position += p.velocity * deltaTime;

            // update the alpha (transparency) of the particle according to its lifetime
            float ratio = p.lifetime / lifeTime;
            vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
    }


private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        // draw the vertex array
        target.draw(vertices, states);
    }

   
    void resetParticle(std::size_t index) {
        // give a random velocity and lifetime to the particle
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        particles[index].lifetime = (std::rand() % 2000) + 1000;

        // reset the position of the corresponding vertex
        vertices[index].position = emitter;
    }

};