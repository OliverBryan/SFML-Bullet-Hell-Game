#ifndef WAVE_HPP
#define WAVE_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

struct Wave {
	std::vector<std::pair<std::string, int>> spawnerTypes;
	int spawners;
	int newSpawnerInterval;
	int waveLength;
};

static bool comment(const std::string& str) {
	bool space = true;
	for (char c : str) {
		if (c == '#')
			return space;
		if (!isspace(c))
			space = false;
	}

	return false;
}

static std::vector<Wave> loadWaves() {
	std::vector<Wave> waves;

	std::ifstream file;
	file.open("waves.dat");
	if (!file) {
		std::cout << "Error: could not open waves.dat" << std::endl;
	}

	std::string line;
	std::vector<std::pair<std::string, int>> spawnerTypes;
	bool inTypes = true;
	int f = 1;
	Wave curWave;
	while (std::getline(file, line)) {
		if ((!line.empty()) && (!comment(line))) {
			if (inTypes) {
				bool first = true;
				std::string spawnerType = "";
				std::string spawnerChanceStr = "";
				for (char c : line) {
					if (c == ':')
						first = false;
					else if (isspace(c)) {}
					else if (first)
						spawnerType += c;
					else if (isdigit(c))
						spawnerChanceStr += c;
				}
				if (spawnerType.find("end") != std::string::npos) {
					inTypes = false;
					curWave.spawnerTypes = spawnerTypes;
				}
				else {
					spawnerTypes.push_back(std::pair<std::string, int>(spawnerType, std::stoi(spawnerChanceStr)));
				}
			}
			else {
				if (f == 1) {
					std::string spawners = "";
					for (char c : line) {
						if (c == '#')
							break;
						if (isspace(c)) continue;
						assert(isdigit(c));
						spawners += c;
					}
					curWave.spawners = std::stoi(spawners);
					f = 2;
				}
				else if (f == 2) {
					std::string spawnerInterval = "";
					for (char c : line) {
						if (c == '#')
							break;
						if (isspace(c)) continue;
						assert(isdigit(c));
						spawnerInterval += c;
					}
					curWave.newSpawnerInterval = std::stoi(spawnerInterval);
					f = 3;
				}
				else if (f == 3) {
					std::string waveTime = "";
					for (char c : line) {
						if (c == '#')
							break;
						if (isspace(c)) continue;
						assert(isdigit(c));
						waveTime += c;
					}
					curWave.waveLength = std::stoi(waveTime);
					waves.push_back(curWave);
					f = 1;
					inTypes = true;
					spawnerTypes.clear();
				}
			}
		}
	}

	return waves;
}

#endif /* WAVE_HPP */