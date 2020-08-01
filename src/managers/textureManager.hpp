#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager{
public:
	// Load texture copy and store it by name
	void load(const std::string &name, sf::Texture texture);
	// Load texture from given path and store it by name
	bool load(const std::string &name, const std::string &path);
	
	bool exists(const std::string &name);
	void unload(const std::string &name);
	
	sf::Texture &get(const std::string &name);
	sf::Vector2u getSize(const std::string &name);

	void setSmooth(const std::string &name, bool n);
	bool isSmooth(const std::string &name);

	void setRepeated(const std::string &name, bool n);
	bool isRepeated(const std::string &name);

private:
	std::map<std::string, sf::Texture> textures;
};
