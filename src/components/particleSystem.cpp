#include "particleSystem.hpp"

#include <cmath>

ParticleSystem::ParticleSystem(unsigned int count) :
	particles(count),
	vertices(sf::Points, count),
	emitterPosition(0.f, 0.f),
	particleLifeTime(3.f, 4.f),
	particleSpeed(50.f, 100.f),
	animationCurve(AnimationCurve::EaseInOut)
{
}

void ParticleSystem::setEmitter(sf::Vector2f position) {
	emitterPosition = position;
}

void ParticleSystem::update(float deltaTime) {
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
		float ratio = p.lifetime / particleLifeTime.getMax();
		vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(vertices, states);
}


void ParticleSystem::resetParticle(std::size_t index) {
	//random angle as radians
	float randomAngle = randomFloat() * emissionAngle * deg2rad - (emissionAngle * 0.5f);

	//random speed between min and max
	float speed = lerp(particleSpeed.getMin(), particleSpeed.getMax(), randomFloat());


	float particleEmitionAngle = emitterRotation * deg2rad + randomAngle;
	particles[index].velocity = sf::Vector2f(
			std::cos(particleEmitionAngle) * speed,
			std::sin(particleEmitionAngle) * speed
	);
	particles[index].lifetime = lerp(particleLifeTime.getMin(), particleLifeTime.getMax(), randomFloat());

	// reset the position of the corresponding vertex
	vertices[index].position = emitterPosition;
}
