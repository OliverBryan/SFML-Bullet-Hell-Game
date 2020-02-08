#ifndef MOD_HPP
#define MOD_HPP

#include <string>
#include "..\spawners\Spawner.hpp"
#include <vector>
#include <Windows.h>

#define SOL_ALL_SAFETIES_ON 1
#include "..\sol.hpp"

class Mod {
public:
	Mod(std::string name, std::string path);

	std::string m_name;
	std::string m_path;

	Spawner* createSpawner(float x, Environment* env, const std::string& name);

	std::vector<std::string> getSpawners();

	friend class Spawner;
	friend class Enemy;
private:
	sol::state m_script;
};

#endif /* MOD_HPP */