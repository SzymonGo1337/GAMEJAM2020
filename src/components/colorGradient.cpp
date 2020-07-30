#include "colorGradient.hpp"
//TODO: tests

ColorGradient::ColorGradient() {}

void ColorGradient::addKey(float position, sf::Color color){
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

int ColorGradient::getKeysCount(){
	return values.size();
}

// undefined behavior for values.size() == 0
ColorGradient::GradientKey ColorGradient::getKey(int index){
	if(index < 0) index = 0;
	else if(index >= values.size()) index = values.size() - 1;
	return values[index];
}


void ColorGradient::setKey(int index, float position, sf::Color color){
	if(index < 0 || index > values.size()) return;

	values[index].position = position;
	values[index].color = color;
}

void ColorGradient::setKey(int index, float position){
	if(index < 0 || index > values.size()) return;

	values[index].position = position;
}

void ColorGradient::setKey(int index, sf::Color color){
	if(index < 0 || index > values.size()) return;

	values[index].color = color;
}

int ColorGradient::getAllKeys(GradientKey *array){
	for (int i = 0 ; i < values.size() ; i++){
		array[0] = values[i];
	}
}

void ColorGradient::removeKey(int index){
	if(index < 0 || index >= values.size()) return;
	values.erase(values.begin() + index);
}
