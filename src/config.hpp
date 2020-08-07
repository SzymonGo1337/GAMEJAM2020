#pragma once

#include <fstream>
#include <map>

class Config {
private:
	std::map<std::string, int> variables;
public:
	Config();
	~Config();
	
	void load(const std::string &path);
	int getValue(const std::string &var);
};