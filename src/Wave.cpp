#include "Wave.hpp"
#include "ModLoader.hpp"
#include "Spawner.hpp"

bool comment(const std::string& str) {
	bool space = true;
	for (char c : str) {
		if (c == '#')
			return space;
		if (!isspace(c))
			space = false;
	}

	return false;
}

int getDifficulty(Wave wave, ModLoader* modLoader) {
	float difficultySum = 0;
	for (const auto& s : wave.spawnerTypes) {
		Mod* spawnerParent = modLoader->getModBySpawnerName(s.first);
		sol::state* spawnerScript = spawnerParent->getScriptForSpawner(s.first, "wave loader");
		int spawnerDifficulty = 0;
		try {
			spawnerDifficulty = (*spawnerScript)[s.first]["difficulty"];
		}
		catch (sol::error e) {
			std::cout << "Error: spawner \"" << s.first << "\" does not define a difficulty" << std::endl;
			abort();
		}
		float difficulty = spawnerDifficulty * (static_cast<float>(s.second) / 100.0f);
		difficultySum += difficulty;
	}
	difficultySum += (wave.spawners + wave.newSpawnerInterval) * 4.0f;
	difficultySum += ((wave.waveLength - (static_cast<float>(wave.spawners * wave.newSpawnerInterval))) * (difficultySum / 100.0f)) * 4.0f;

	return static_cast<int>(difficultySum);
}

std::vector<Wave> loadWaves(ModLoader* modLoader) {
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
				bool commentSeen = false;
				std::string spawnerType = "";
				std::string spawnerChanceStr = "";
				for (char c : line) {
					if (c == ':')
						first = false;
					else if (c == '#')
						commentSeen = true;
					else if (isspace(c)) {}
					else if (first)
						spawnerType += c;
					else if (isdigit(c) && !commentSeen)
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

	for (int i = 0; i < waves.size(); i++) {
		std::cout << "Wave " << (i + 1) << " difficulty: " << getDifficulty(waves[i], modLoader) << std::endl;
	}

	return waves;
}

Wave getWave(int number) {
	int newSpawnerInterval = irand(2, 10);

	return Wave();
}

std::vector<Wave> newLoadWaves() {
	std::vector<Wave> waves;



	return waves;
}