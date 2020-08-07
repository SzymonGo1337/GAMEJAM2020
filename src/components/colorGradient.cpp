#include "colorGradient.hpp"

#include <stdexcept>

ColorGradient::GradientKey::GradientKey() : // default
	position(-1),
	color(0,0,0) {}

ColorGradient::GradientKey::GradientKey(const GradientKey &org) : // copy
	position(org.position),
	color(org.color) {} 

ColorGradient::GradientKey::GradientKey(float pPosition, sf::Color pColor) : // parametric
	position(pPosition),
	color(pColor) {}

ColorGradient::ColorGradient() {
}

ColorGradient::ColorGradient(std::initializer_list<sf::Color> colors) {
	unsigned int size = colors.size();
	if(size <= 0) return;

	values.resize(size);
	if(size == 1) { // special case
		values[0].position = 0;
		values[0].color = *(colors.begin());
		return;
	}

	float step = 1.0f / (size-1);
	int i = 0;

	std::initializer_list<sf::Color>::iterator it;
	for(it = colors.begin() ; it != colors.end() ; ++it, ++i){
		values[i].position = step * i;
		values[i].color = *it;
	}
}

ColorGradient::ColorGradient(std::initializer_list<GradientKey> keys) {
	float lastPos = 0;
	unsigned int size = keys.size();

	values.resize(size);
	if(size==0) throw std::invalid_argument("param 'keys' is empty");
	std::initializer_list<GradientKey>::iterator it;

	int i = 0;
	for(it = keys.begin() ; it != keys.end() ; ++it, ++i){
		if(it->position < lastPos) throw std::invalid_argument("keys are not in order");
		if(it->position > 1) throw std::invalid_argument("one or more of keys are >1");
		lastPos = it->position;
		
		values[i].color = it->color;
		values[i].position = it->position;
	}
}

void ColorGradient::addKey(float position, sf::Color color) {
	if(position < 0) position = 0;
	else if(position > 1) position = 1;

	std::vector<GradientKey>::iterator it = values.begin();
	bool notInserted = true;
	while (it < values.end()) {
		if(it->position > position){
			values.insert(it, GradientKey(position, color));
			notInserted = false;
			break;
		}
		it++;
	}
	if(notInserted){
		values.push_back(GradientKey(position, color));
	}

}

unsigned int ColorGradient::getKeysCount() const {
	return values.size();
}

// undefined behavior for values.size() == 0
ColorGradient::GradientKey ColorGradient::getKey(unsigned int index) const {
	if(index >= values.size()) index = values.size() - 1;
	return values[index];
}

void ColorGradient::setKey(unsigned int index, float position, sf::Color color) {
	if(index >= values.size()) return;

	float left = -1;
	float right = 2;
	if(index > 0) left = values[index-1].position;
	else if(index+1 < values.size()) right = values[index+1].position;
	
	// Check if point will be in corect position after change
	if(left <= position && position <= right){
		values[index].position = position;
		values[index].color = color;
	}
	else { 
		// lazy position correction (remove & insert)
		values.erase(values.begin()+index);
		addKey(position, color);
	}
}

void ColorGradient::setKey(unsigned int index, float position) {
	setKey(index, position, values[index].color);
}

void ColorGradient::setKey(unsigned int index, sf::Color color) {
	if(index >= values.size()) return;

	values[index].color = color;
}

void ColorGradient::getAllKeys(GradientKey *array) const {
	for (size_t i = 0 ; i < values.size() ; i++){
		array[0] = values[i];
	}
}

void ColorGradient::removeKey(unsigned int index) {
	if(index >= values.size()) return;
	values.erase(values.begin() + index);
}

unsigned int ColorGradient::getLeftKeyIndexFor(float position) const {
	unsigned int last = 0;
	// gradients do not have a lot of points so O(n) is good enough
	for(size_t i = 0 ; i < values.size() && values[i].position < position; i++){
		last = i;
	}
	
	return last;
}

// Not in ColorGradient. Just for use in ColorGradient::evaluate
inline sf::Uint8 LerpColorComponent(sf::Uint8 start, sf::Uint8 end, float t) {
	return (sf::Uint8)((end - start) * t + start);
}

sf::Color ColorGradient::evaluate(float position) const {
	unsigned int index = getLeftKeyIndexFor(position);

	if(index + 1 >= getKeysCount()){ //its last point
		return values[index].color;
	}

	GradientKey startKey = values[index];
	GradientKey endKey = values[index+1];

	sf::Color startColor = startKey.color;
	sf::Color endColor = endKey.color;

	position = clamp(position, startKey.position, endKey.position);

	// map position in [start ; end] to position in [0 ; 1]
	float t = (position - startKey.position) * (1.0f / (endKey.position - startKey.position));
	
	// color = Lerp(startColor, endColor, t)
	sf::Uint8 r = LerpColorComponent(startColor.r, endColor.r, t);
	sf::Uint8 g = LerpColorComponent(startColor.g, endColor.g, t);
	sf::Uint8 b = LerpColorComponent(startColor.b, endColor.b, t);
	sf::Uint8 a = LerpColorComponent(startColor.a, endColor.a, t);

	return sf::Color(r, g, b, a);
}

