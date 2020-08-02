#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class FontManager{
public:
	// Load font copy and store it by name
	void load(const std::string &name, sf::Font font);
	// Load texture from given path and store it by name
	bool load(const std::string &name, const std::string &path);

	bool exists(const std::string &name);
	void unload(const std::string &name);

	sf::Font &get(const std::string &name);

private:
	std::map<std::string, sf::Font> fonts;
};
