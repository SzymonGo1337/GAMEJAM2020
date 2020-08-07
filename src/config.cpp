#include "config.hpp"

#include <algorithm>
#include <iostream>

Config::Config() {
	
}

Config::~Config() {
	variables.clear();
}

void Config::load(const std::string &path) {

	std::fstream file;
	file.open(path, std::ios::in);

	if(file.good()) {
		
		if(file.is_open()) {

			std::string line;
			int middle; //idk how to name it 

			while(getline(file, line)) {	
				line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
				if(line.empty() || line[0] == '#')
					continue;
				
				middle = line.find('=');

				variables[line.substr(0, middle)] = std::stoi(line.substr(middle+1, line.size()));
			}
		}
	}
	file.close();
}

int Config::getValue(const std::string &var) {
	
	if(variables.count(var)) {

		return variables.at(var);

	} else {

		throw std::invalid_argument("[ERROR] cannot find " + var + " variable in config file");
	}
	
}