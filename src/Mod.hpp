#ifndef MOD_HPP
#define MOD_HPP

#include <string>
#include "Spawner.hpp"
#include <vector>
#include <map>
#include <Windows.h>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

class Powerup;

class Mod {
public:
	Mod(std::string name, std::string path);
	~Mod();

	std::string m_name;
	std::string m_path;

	Spawner* createSpawner(float x, Environment* env, const std::string& name);
	Powerup* createPowerup(float x, float y, const std::string& name);
	
	sol::state* getScriptForSpawner(const std::string& name, const std::string& origin);
	sol::state* getScriptForPowerup(const std::string& name);

	static void initializeScript(sol::state& script);

	std::vector<std::string> getSpawners();
	std::vector<std::string> getPowerups();

	friend class Spawner;
	friend class Enemy;
	friend class Powerup;
private:
	sol::state m_mainScript;
	std::vector<sol::state*> m_spawnerScripts;
	std::vector<sol::state*> m_powerupScripts;
	std::map<std::string, sf::Texture*> m_textures;
};

#endif /* MOD_HPP */