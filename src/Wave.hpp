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
};

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
	bool fl = true;
	Wave curWave;
	while (std::getline(file, line)) {
		if (!line.empty()) {
			if (inTypes) {
				bool first = true;
				std::string spawnerType = "";
				std::string spawnerChanceStr = "";
				for (char c : line) {
					if (c == ':')
						first = false;
					else if (first)
						spawnerType += c;
					else if (isdigit(c))
						spawnerChanceStr += c;
				}
				if (spawnerType == "end") {
					inTypes = false;
					curWave.spawnerTypes = spawnerTypes;
				}
				else {
					spawnerTypes.push_back(std::pair<std::string, int>(spawnerType, std::stoi(spawnerChanceStr)));
				}
			}
			else {
				if (fl) {
					std::string spawners = "";
					for (char c : line) {
						assert(isdigit(c));
						spawners += c;
					}
					curWave.spawners = std::stoi(spawners);
					fl = false;
				}
				else {
					std::string spawnerInterval = "";
					for (char c : line) {
						assert(isdigit(c));
						spawnerInterval += c;
					}
					curWave.newSpawnerInterval = std::stoi(spawnerInterval);
					waves.push_back(curWave);
					spawnerTypes.clear();
					fl = true;
					inTypes = true;
				}
			}
		}
	}
 
	/*
	Wave wave1;
	wave1.spawnerTypes.push_back(std::pair<std::string, int>("basic", 100));
	wave1.spawners = 5;
	wave1.newSpawnerInterval = 4;
	waves.push_back(wave1);

	Wave wave2;
	wave2.spawnerTypes.push_back(std::pair<std::string, int>("basic", 100));
	wave2.spawners = 8;
	wave2.newSpawnerInterval = 4;
	waves.push_back(wave2);

	Wave wave3;
	wave3.spawnerTypes.push_back(std::pair<std::string, int>("laser", 60));
	wave3.spawnerTypes.push_back(std::pair<std::string, int>("basic", 40));
	wave3.spawners = 5;
	wave3.newSpawnerInterval = 5;
	waves.push_back(wave3);

	Wave wave4;
	wave4.spawnerTypes.push_back(std::pair<std::string, int>("laser", 60));
	wave4.spawnerTypes.push_back(std::pair<std::string, int>("basic", 40));
	wave4.spawners = 8;
	wave4.newSpawnerInterval = 3;
	waves.push_back(wave4);

	Wave wave5;
	wave5.spawnerTypes.push_back(std::pair<std::string, int>("homing", 100));
	wave5.spawners = 3;
	wave5.newSpawnerInterval = 7;
	waves.push_back(wave5);

	Wave wave6;
	wave6.spawnerTypes.push_back(std::pair<std::string, int>("basic", 40));
	wave6.spawnerTypes.push_back(std::pair<std::string, int>("laser", 30));
	wave6.spawnerTypes.push_back(std::pair<std::string, int>("homing", 30));
	wave6.spawners = 10;
	wave6.newSpawnerInterval = 7;
	waves.push_back(wave6);

	Wave wave7;
	wave7.spawnerTypes.push_back(std::pair<std::string, int>("ricochet", 100));
	wave7.spawners = 2;
	wave7.newSpawnerInterval = 10;
	waves.push_back(wave7);

	Wave wave8;
	wave8.spawnerTypes.push_back(std::pair<std::string, int>("shotgun", 100));
	wave8.spawners = 2;
	wave8.newSpawnerInterval = 10;
	waves.push_back(wave8);

	Wave wave9;
	wave9.spawnerTypes.push_back(std::pair<std::string, int>("ricochet", 40));
	wave9.spawnerTypes.push_back(std::pair<std::string, int>("shotgun", 40));
	wave9.spawnerTypes.push_back(std::pair<std::string, int>("homing", 20));
	wave9.spawners = 5;
	wave9.newSpawnerInterval = 8;
	waves.push_back(wave9);
	*/

	return waves;
}

#endif /* WAVE_HPP */