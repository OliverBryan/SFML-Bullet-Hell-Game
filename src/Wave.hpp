#ifndef WAVE_HPP
#define WAVE_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <array>
#include <random>

struct Wave {
	std::vector<std::pair<std::string, int>> spawnerTypes;
	int spawners;
	int newSpawnerInterval;
	int waveLength;
};

class ModLoader;

int getDifficulty(Wave wave, ModLoader* modLoader);
bool comment(const std::string& str);

// Old loading system
std::vector<Wave> loadWaves(ModLoader* modLoader);

Wave getRandomWave(float difficulty, ModLoader* modLoader);
std::vector<Wave> newLoadWaves(ModLoader* modLoader);

#endif /* WAVE_HPP */