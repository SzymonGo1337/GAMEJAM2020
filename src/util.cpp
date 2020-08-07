#include "util.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include <map>

MinMaxf::MinMaxf(float min, float max){
	if(max < min){
		float tmp = max;
		max = min;
		min = tmp;
	}
	this->min = min;
	this->max = max;
}

MinMaxf::MinMaxf(const MinMaxf &o) : min(o.min), max(o.max) {
}

float MinMaxf::getMin() const {
	return min;
}

float MinMaxf::getMax() const {
	return max;
}

std::ostream& operator<< (std::ostream &out, const MinMaxf &mm){
	out << "["<< mm.min << ";"<< mm.max << "]";
	return out;
}

MinMaxi::MinMaxi(int min, int max) {
	if(max < min){
		int tmp = max;
		max = min;
		min = tmp;
	}
	this->min = min;
	this->max = max;
}

MinMaxi::MinMaxi(const MinMaxi &o) : min(o.min), max(o.max) {
}

int MinMaxi::getMin() const {
	return min;
}

int MinMaxi::getMax() const {
	return max;
}

float lerp(float start, float end, float t) {
	return (end - start) * t + start;
}

float clamp(float value, float min, float max) {
	if(value < min) return min;
	if(value > max) return max;
	return value;
}

int clamp(int value, int min, int max) { 
	if(value < min) return min;
	if(value > max) return max;
	return value;
}

float sign(float x){
	return (0 < x) - (x < 0);
}

float randomFloat() {
	return std::rand()/float(RAND_MAX);
}


std::ostream& operator<<(std::ostream &out, const sf::Color &c) {
	out << "rgba{" << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ", " << (int)c.a << "}";
	return out;
}
std::ostream& operator<<(std::ostream &out, const sf::Vector2f &v){
	out << "[" << v.x << ";" << v.y << "]";
	return out;
}



std::string tostr(float x){
	return std::to_string(x);
}
std::string tostr(int x){
	return std::to_string(x);
}


std::map<std::string, sf::Text> logMap;

sf::Font *font = NULL;

sf::Font* getDefaultFont(){
	if(font == NULL){
		font = new sf::Font();
		font->loadFromFile("res/fonts/Ubuntu-Bold.ttf");
	}
	return font;
}

void setKey(const std::string &key, const std::string &value){
	if(logMap.count(key)>0){
		logMap[key].setString(key + ": " + value);
	}
	else {
		sf::Text t;
		t.setString(key + ": " + value);
		t.setFont(*getDefaultFont());
		t.setCharacterSize(16);
		logMap.insert(std::pair<std::string, sf::Text>(key, t));
	}
}
void removeKey(const std::string &key){
	logMap.erase(key);
}

std::map<std::string, sf::Text> &getLogMap() {
	return logMap;
}