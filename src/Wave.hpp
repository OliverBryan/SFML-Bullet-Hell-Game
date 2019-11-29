#ifndef WAVE_HPP
#define WAVE_HPP

#include <vector>
#include <string>

struct Wave {
	std::vector<std::pair<std::string, int>> spawnerTypes;
	int spawners;
	int newSpawnerInterval;
};

static std::vector<Wave> loadWaves() {
	std::vector<Wave> waves;

	Wave wave1;
	wave1.spawnerTypes.push_back(std::pair<std::string, int>("basic", 100));
	wave1.spawners = 100;
	wave1.newSpawnerInterval = 1;
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

	return waves;
}

#endif /* WAVE_HPP */