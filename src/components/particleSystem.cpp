#include "particleSystem.hpp"

#include <cmath>

ParticleSystem::ParticleSystem(unsigned int count) :
	particles(count),
	vertices(sf::Quads, count*4),
	debugArr(sf::Lines, 6),
	unusedParticles(count),
	textureSize(1,1),
	emitterPosition(0.f, 0.f),
	emitterShape(new ParticleSystemShape(46, 0)),  //memory leak
	particleLifeTime(3.f, 4.f),
	particleSpeed(50.f, 100.f),
	particleColorOverLifetime({sf::Color::White}),
	colorAnimationCurve(AnimationCurve::EaseInOut),
	scaleOverLifetime(AnimationCurve::One),
	rotationSpeedScaleOverLifetime(AnimationCurve::One)
{
	resetEmitter();
}

float mag(const sf::Vector2f &v){
	return sqrt(v.x * v.x + v.y * v.y);
}

float sign(float v){
	return (0 < v) - (v < 0);
}

void ParticleSystem::update() {
	currentEmissionTime += GameTime::dt();

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

		if(p.lifetime <= 0){ // just die
			setParticleColor(i, sf::Color::Transparent);
			++unusedParticles;
		}	

		
		float lifeTimeRatio = clamp(p.lifetime / particleLifeTime.getMax(), 0.f, 1.f);
		float gradientPos = colorAnimationCurve(1 - lifeTimeRatio);
		sf::Color color = particleColorOverLifetime.evaluate(gradientPos);;
		float scale = particleSize * scaleOverLifetime(gradientPos);
		
		p.velocity += particleGravity * deltaTime;
		p.position += p.velocity * deltaTime;
		p.rotation += particleRotationSpeed * rotationSpeedScaleOverLifetime(gradientPos) * deltaTime;
		float a = p.rotation * deg2rad;

		for(unsigned int iv = 0 ; iv < 4 ; iv++){
			
			float x = sign(vertices[i*4 +iv].texCoords.x);
			float y = sign(vertices[i*4 +iv].texCoords.y);
			/*
			Rotation matrix:
				cos     -sin
				sin      cos
			*/
			float rx =        x * cos(a) + y * sin(a);
			float ry =  1.f - x * sin(a) + y * cos(a);

			sf::Vector2f newPosition = sf::Vector2f(rx * scale, ry * scale);

			vertices[i*4 +iv].position = newPosition + p.position;
			vertices[i*4 +iv].color = color;
		}
	}

	updateDebug(deltaTime);
}

void ParticleSystem::setParticleColor(std::size_t index, const sf::Color &color){
	for(unsigned int iv = 0 ; iv < 4 ; iv++){
		vertices[index*4 +iv].color = color;
	}
}

void ParticleSystem::updateDebug(float deltaTime) {
	if(!debugDraw) return;
	emitterShape->debugDraw(debugArr, emitterPosition);
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = texture;

	// draw the vertex array
	target.draw(vertices, states);

	if(debugDraw) target.draw(debugArr, states);
}


void ParticleSystem::emitParticle(std::size_t index) {

	particles[index].velocity = emitterShape->getParticleVelocity(particleSpeed);

	particles[index].lifetime = lerp(particleLifeTime.getMin(), particleLifeTime.getMax(), randomFloat());

	particles[index].position = emitterShape->getParticlePosition() + emitterPosition;

	vertices[index*4 +0].position = emitterPosition + (sf::Vector2f(-1, -1) * particleSize);
	vertices[index*4 +0].position = emitterPosition + (sf::Vector2f(-1,  1) * particleSize);
	vertices[index*4 +0].position = emitterPosition + (sf::Vector2f(1 ,  1) * particleSize);
	vertices[index*4 +0].position = emitterPosition + (sf::Vector2f(1 , -1) * particleSize);
	

	--unusedParticles;
}

bool ParticleSystem::finished() const {
	return currentEmissionTime > emissionTime;
}

void ParticleSystem::resetEmitter() {
	lastEmittedParticleIndex = 0;
	unusedParticles = particles.size();
	currentEmissionTime = 0;
	for(unsigned int i = 0 ; i < particles.size() ; i++){
		particles[i].lifetime = 0;
		// texCoords
		vertices[i*4 +0].texCoords = sf::Vector2f( 0           , 0);
		vertices[i*4 +1].texCoords = sf::Vector2f( 0           , textureSize.y);
		vertices[i*4 +2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
		vertices[i*4 +3].texCoords = sf::Vector2f(textureSize.x, 0);
		// color
		setParticleColor(i, sf::Color::Transparent);
	}
}

float ParticleSystem::getEmissionTimeElapsed() const {
	return currentEmissionTime;
}

int ParticleSystem::getFreeParticlesCount() const {
	return unusedParticles;
}

int ParticleSystem::getUsedParticlesCount() const {
	return particles.size() - unusedParticles;
}

unsigned int ParticleSystem::getParticlesCount() const {
	return particles.size();
}

void ParticleSystem::updateTextureSize(sf::Vector2f texSize){
	this->textureSize = texSize;

	for(unsigned int i = 0 ; i < particles.size() ; i++){
		vertices[i*4 +0].texCoords = sf::Vector2f(0        , 0);
		vertices[i*4 +1].texCoords = sf::Vector2f(0        , texSize.y);
		vertices[i*4 +2].texCoords = sf::Vector2f(texSize.x, texSize.y);
		vertices[i*4 +3].texCoords = sf::Vector2f(texSize.x, 0);
	}
}

sf::Vector2f velocityRotationAngle(float rotation, float angle, const MinMax &pSpeed){
	//random angle as radians
	float randomAngle = randomFloat() * angle - (angle * 0.5f);

	//random speed between min and max
	float speed = lerp(pSpeed.getMin(), pSpeed.getMax(), randomFloat());


	float particleEmitionAngle = (rotation + randomAngle) * deg2rad;
	return sf::Vector2f(
			std::cos(particleEmitionAngle) * speed,
			std::sin(particleEmitionAngle) * speed
	);
}

sf::Vector2f ParticleSystemShape::getParticlePosition() const {
	return sf::Vector2f(0,0);
}
sf::Vector2f ParticleSystemShape::getParticleVelocity(const MinMax &speed) const {
	return velocityRotationAngle(rotation, angle, speed);
}

sf::Vector2f ParticleSystemShapeBox::getParticlePosition() const {
	float x = (randomFloat()-0.5f) * size.x;
	float y = (randomFloat()-0.5f) * size.y;
	float rot = rotation * deg2rad;

	float rx =      x * sin(rot) + y * cos(rot);
	float ry = -1 * x * cos(rot) + y * sin(rot);

	return sf::Vector2f(rx, ry);
}
sf::Vector2f ParticleSystemShapeBox::getParticleVelocity(const MinMax &speed) const {
	return velocityRotationAngle(rotation, angle, speed);
}

void drawRotationAngleDebug(sf::VertexArray &debugArr, float rotation, float angle, sf::Vector2f position){
	// ugly debug draw
	debugArr[0].color = debugArr[1].color = sf::Color::Red;
	debugArr[2].color = debugArr[3].color = sf::Color::Red;
	debugArr[4].color = debugArr[5].color = sf::Color::Green;

	debugArr[0].position = debugArr[2].position = debugArr[4].position = position;

	debugArr[5].position = position + sf::Vector2f(
		std::cos(rotation * deg2rad) * 100,
		std::sin(rotation * deg2rad) * 100
	);

	float limitMin = (rotation - angle * 0.5f) * deg2rad;
	float limitMax = (rotation + angle * 0.5f) * deg2rad;

	debugArr[1].position = position + sf::Vector2f(
		std::cos(limitMin) * 100,
		std::sin(limitMin) * 100
	);

	debugArr[3].position = position + sf::Vector2f(
		std::cos(limitMax) * 100,
		std::sin(limitMax) * 100
	);
}

void ParticleSystemShape::debugDraw(sf::VertexArray &debugArr, sf::Vector2f position) const {
	if(debugArr.getVertexCount() != 6)
		debugArr.resize(6);

	drawRotationAngleDebug(debugArr, rotation, angle, position);
}

void ParticleSystemShapeBox::debugDraw(sf::VertexArray &debugArr, sf::Vector2f position) const {
	if(debugArr.getVertexCount() != 14)
		debugArr.resize(14);

	drawRotationAngleDebug(debugArr, rotation, angle, position);

	for(int i = 6 ; i < 14 ; i++)
		debugArr[i].color = sf::Color::Blue;
	
	
	float sx = size.x * 0.5f;
	float sy = size.y * 0.5f;

	/*
	6     7   
 13 +-----+ 8
    |     |
    |     |
 12 +-----+ 9
	11    10
	*/
	debugArr[13].position = debugArr[6].position  = sf::Vector2f( sx,  sy);
	debugArr[8].position  = debugArr[7].position  = sf::Vector2f( sx, -sy);
	debugArr[9].position  = debugArr[10].position = sf::Vector2f(-sx, -sy);
	debugArr[12].position = debugArr[11].position = sf::Vector2f(-sx,  sy);

	for(int i = 6 ; i < 14 ; i++){
		float x = debugArr[i].position.x;
		float y = debugArr[i].position.y;
		
		float rot = rotation * deg2rad;

		float rx =      x * sin(rot) + y * cos(rot);
		float ry = -1 * x * cos(rot) + y * sin(rot);

		debugArr[i].position = position - sf::Vector2f(rx, ry);
	}
}
