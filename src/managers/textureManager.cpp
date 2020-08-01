#include "textureManager.hpp"

bool TextureManager::load(const std::string &name, const std::string &path){
	bool success = false;
	sf::Texture texture;

	if(texture.loadFromFile(path)){
		textures[name] = texture;
		success = true;
	}

	return success;
}

void TextureManager::load(const std::string &name, sf::Texture texture){
	textures[name] = texture;
}

bool TextureManager::exists(const std::string &name){
	return (textures.find(name) != textures.end());
}

void TextureManager::unload(const std::string &name){
	textures.erase(name);
}

sf::Texture &TextureManager::get(const std::string &name){
	return textures[name];
}

sf::Vector2u TextureManager::getSize(const std::string &name){
	return textures[name].getSize();
}

void TextureManager::setSmooth(const std::string &name, bool n){
	textures[name].setSmooth(n);
}

bool TextureManager::isSmooth(const std::string &name){
	return textures[name].isSmooth();
}

void TextureManager::setRepeated(const std::string &name, bool n){
	textures[name].setRepeated(n);
}

bool TextureManager::isRepeated(const std::string &name){
	return textures[name].isRepeated();
}
