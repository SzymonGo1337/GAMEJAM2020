#include "fontManager.hpp"

bool FontManager::load(const std::string &name, const std::string &path){
	bool success = false;
	sf::Font font;

	if(font.loadFromFile(path)){
		fonts[name] = font;
		success = true;
	}

	return success;
}

void FontManager::load(const std::string &name, sf::Font font){
	fonts[name] = font;
}

bool FontManager::exists(const std::string &name){
	return (fonts.find(name) != fonts.end());
}

void FontManager::unload(const std::string &name){
	fonts.erase(name);
}

sf::Font &FontManager::get(const std::string &name){
	return fonts[name];
}
