#include "particleSystem.hpp"

#include <cmath>

ParticleSystem::ParticleSystem(unsigned int count) :
	particles(count),
	vertices(sf::Points, count),
	debugArr(sf::Lines, 6),
	unusedParticles(count),
	emitterPosition(0.f, 0.f),
	particleLifeTime(3.f, 4.f),
	particleSpeed(50.f, 100.f),
	particleColor({sf::Color::White}),
	colorAnimationCurve(AnimationCurve::EaseInOut)
{
	resetEmitter();
}

void ParticleSystem::update(float deltaTime) {
	currentEmissionTime += deltaTime;

	// ========== emission
	if(unusedParticles > 0 && (emissionTime < 0 || currentEmissionTime < emissionTime)){
		if(particlesToEmit > 1){
			int nowEmitted = (int)particlesToEmit;
			nowEmitted = clamp(nowEmitted, 0, unusedParticles); //limit to free particles

			particlesToEmit -= nowEmitted;
			while (nowEmitted--) {
				lastEmittedParticleIndex = (lastEmittedParticleIndex+1) % particles.size();
				emitParticle(lastEmittedParticleIndex);
			}
			
		}
		particlesToEmit += emissionRate * deltaTime;
	}
	// ========== update
	for (std::size_t i = 0; i < particles.size(); ++i) {
		Particle& p = particles[i];

		if (p.lifetime <= 0){ // already dead
			continue;
		}

		p.lifetime -= deltaTime;

		if(p.lifetime <= 0){ // just dead
			vertices[i].color = sf::Color::Transparent;
			++unusedParticles;
		}	

		vertices[i].position += p.velocity * deltaTime;

		float lifeTimeRatio = clamp(p.lifetime / particleLifeTime.getMax(), 0.f, 1.f);
		float gradientPos = colorAnimationCurve(1 - lifeTimeRatio);
		vertices[i].color = particleColor.evaluate(gradientPos);
		
	}

	updateDebug(deltaTime);
}

void ParticleSystem::updateDebug(float deltaTime) {
	if(!debugDraw) return;
	// ugly debug draw
	debugArr[0].color = debugArr[1].color = sf::Color::Red;
	debugArr[2].color = debugArr[3].color = sf::Color::Red;
	debugArr[4].color = debugArr[5].color = sf::Color::Green;

	debugArr[0].position = debugArr[2].position = debugArr[4].position = emitterPosition;

	debugArr[5].position = emitterPosition + sf::Vector2f(
		std::cos(emitterRotation * deg2rad) * 100,
		std::sin(emitterRotation * deg2rad) * 100
	);

	float limitMin = (emitterRotation - emissionAngle * 0.5f) * deg2rad;
	float limitMax = (emitterRotation + emissionAngle * 0.5f) * deg2rad;

	debugArr[1].position = emitterPosition + sf::Vector2f(
		std::cos(limitMin) * 100,
		std::sin(limitMin) * 100
	);

	debugArr[3].position = emitterPosition + sf::Vector2f(
		std::cos(limitMax) * 100,
		std::sin(limitMax) * 100
	);
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(vertices, states);

	if(debugDraw) target.draw(debugArr, states);
}


void ParticleSystem::emitParticle(std::size_t index) {
	//random angle as radians
	float randomAngle = randomFloat() * emissionAngle - (emissionAngle * 0.5f);

	//random speed between min and max
	float speed = lerp(particleSpeed.getMin(), particleSpeed.getMax(), randomFloat());


	float particleEmitionAngle = (emitterRotation + randomAngle) * deg2rad;
	particles[index].velocity = sf::Vector2f(
			std::cos(particleEmitionAngle) * speed,
			std::sin(particleEmitionAngle) * speed
	);
	particles[index].lifetime = lerp(particleLifeTime.getMin(), particleLifeTime.getMax(), randomFloat());

	// reset the position of the corresponding vertex
	vertices[index].position = emitterPosition;

	--unusedParticles;
}

bool ParticleSystem::finished() {
	return currentEmissionTime > emissionTime;
}

void ParticleSystem::resetEmitter() {
	lastEmittedParticleIndex = 0;
	unusedParticles = particles.size();
	currentEmissionTime = 0;
	for(unsigned int i = 0 ; i < particles.size() ; i++){
		particles[i].lifetime = 0;
		vertices[i].color = sf::Color::Transparent;
	}
}

float ParticleSystem::getEmissionTimeElapsed() {
	return currentEmissionTime;
}

int ParticleSystem::getFreeParticlesCount() {
	return unusedParticles;
}

int ParticleSystem::getUsedParticlesCount() {
	return particles.size() - unusedParticles;
}

int ParticleSystem::getParticlesCount() {
	return particles.size();
}