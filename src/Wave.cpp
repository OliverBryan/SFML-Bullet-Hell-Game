#include "Wave.hpp"
#include "ModLoader.hpp"
#include "Spawner.hpp"
#include <cmath>
#include <iterator>
#include <type_traits>
#include <numeric>

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

float calculateSpawnerDifficulty(std::vector<std::pair<std::string, int>> spawners, ModLoader* modLoader) {
	float difficultySum = 0;
	for (const auto& s : spawners) {
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
		float difficulty = (spawnerDifficulty * (static_cast<float>(s.second) / 100.0f));
		difficultySum += difficulty;
	}
	return difficultySum;
}

int getDifficulty(Wave wave, ModLoader* modLoader) {
	float difficultySum = 0;
	difficultySum += calculateSpawnerDifficulty(wave.spawnerTypes, modLoader);
	difficultySum *= (std::pow(wave.spawners, 1.5) + (wave.waveLength - ((wave.spawners * wave.newSpawnerInterval) / 3.0f)));

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

	return waves;
}

static std::vector<std::string> possibleSpawnerTypes;

int wrand(std::vector<int> possibilites, std::vector<int> weights) {
	return 0;
}

void printWave(Wave wave, ModLoader* modLoader) {
	std::cout << "Wave: " << std::endl << "Spawners: " << wave.spawners << std::endl << "Spawner Interval: " << wave.newSpawnerInterval << std::endl << "Length: " << wave.waveLength << std::endl;
	for (auto s : wave.spawnerTypes) {
		std::cout << s.first << ": " << s.second << std::endl;
	}
	std::cout << "Difficulty: " << getDifficulty(wave, modLoader) << std::endl;
	std::cout << std::endl;
}

std::string getRandomSpawner(float difficulty, ModLoader* modLoader) {
	std::vector<int> spawnerWeights;
	std::vector<int> totalSpawners;
	int i = 0;
	for (std::string spawner : possibleSpawnerTypes) {
		float spawnerDifficulty = (*modLoader->getModBySpawnerName(spawner)->getScriptForSpawner(spawner, "origin"))[spawner]["difficulty"];
		spawnerWeights.push_back((1 / (1 + std::abs(difficulty - spawnerDifficulty))) * 5000);
		totalSpawners.push_back(i);
		i++;
	}
	std::piecewise_constant_distribution<> dist(totalSpawners.begin(), totalSpawners.end(), spawnerWeights.begin());
	std::random_device rd;
	std::mt19937 gen{ rd() };
	return possibleSpawnerTypes[dist(gen)];
}

std::vector<int> weights { 70, 60, 30, 20, 10, 5 };
Wave getRandomWave(float difficulty, ModLoader* modLoader) {
	Wave wave;

	int possibilities[]{ 1, 2, 3, 4, 5, 6 };
	std::piecewise_constant_distribution<> dist(std::begin(possibilities), std::end(possibilities), std::begin(weights));
	std::random_device rd;
	std::mt19937 gen{ rd() };
	int amountOfSpawners = dist(gen);

	int sum = 0;
	std::vector<float> nums;
	for (			int i = 0; i < amountOfSpawners; i++) {
		int n = irand(0, 100);
		sum += n;
		nums.push_back(n);
	}
	for (float& i : nums) {
		i /= sum;
		i *= 100.0f;
	}
	std::vector<int> spawnerChances;
	int is = 0;
	for (float i : nums) {
		spawnerChances.push_back(std::round(i));
		is += std::round(i);
	}
	spawnerChances[spawnerChances.size() - 1] += 100 - is;
	std::sort(spawnerChances.rbegin(), spawnerChances.rend());


	std::vector<std::string> localPossibleSpawnerTypes = possibleSpawnerTypes;
	for (int x = 0; x < amountOfSpawners; x++) {
		std::vector<int> spossibilites(localPossibleSpawnerTypes.size());
		std::iota(spossibilites.begin(), spossibilites.end(), 0);

		std::vector<int> sweights;
		for (int i = 0; i < localPossibleSpawnerTypes.size(); i++) {
			float sdiff = (*modLoader->getModBySpawnerName(localPossibleSpawnerTypes[i])->getScriptForSpawner(localPossibleSpawnerTypes[i], "waves"))[localPossibleSpawnerTypes[i]]["difficulty"];
			float weight = std::pow((1 / (1 + std::abs(difficulty - sdiff))) * 2000.0f, 2);
			sweights.push_back(weight);
		}
		std::piecewise_constant_distribution<> dist(spossibilites.begin(), spossibilites.end(), sweights.begin());
		std::random_device rd;
		std::mt19937 gen{ rd() };
		int s = dist(gen);
		wave.spawnerTypes.push_back(std::make_pair(localPossibleSpawnerTypes[s], spawnerChances[x]));
		localPossibleSpawnerTypes.erase(localPossibleSpawnerTypes.begin() + s);
	}

	float spawnerDifficulty = calculateSpawnerDifficulty(wave.spawnerTypes, modLoader);
	if (spawnerDifficulty > 100) spawnerDifficulty = 100;
	wave.spawners = irand(2, 13 - std::round(spawnerDifficulty / 10));
	wave.newSpawnerInterval = irand(2, 14 - wave.spawners);
	wave.waveLength = irand(wave.spawners * wave.newSpawnerInterval, wave.spawners * wave.newSpawnerInterval * 1.5);

	return wave;
}

void rampWeights() {
	weights[0] *= 0.8;
	weights[1] *= 0.95;
	weights[2] *= 1.2;
	weights[3] *= 1.2;
	weights[4] *= 1.3;
	weights[5] *= 1.3;

	if (weights[0] < 2) weights[0] = 2;
	if (weights[1] < 10) weights[1] = 10;
	if (weights[2] > 400) weights[2] = 400;
	if (weights[3] > 400) weights[3] = 400;
	if (weights[4] > 380) weights[4] = 380;
	if (weights[5] > 350) weights[5] = 350;
}

std::vector<Wave> newLoadWaves(ModLoader* modLoader) {
	for (Mod* mod : modLoader->getMods())
		for (std::string spawner : mod->getSpawners())
			possibleSpawnerTypes.push_back(spawner);

	std::vector<Wave> waves;

	float targetDifficulty = 10;
	for (int i = 0; i < 100; i++) {
		Wave wave = getRandomWave(targetDifficulty, modLoader);
		rampWeights();
		targetDifficulty += irand(3, 7);
		if (targetDifficulty > 100) targetDifficulty = 100;
		waves.push_back(wave);
	}

	return waves;
}