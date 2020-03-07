#include "ModLoader.hpp"
#include <iostream>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

ModLoader::ModLoader() {}

ModLoader::~ModLoader() {
	// Iterate through the mod objects, and delete each one
	for (int i = 0; i < m_mods.size(); i++) {
		Mod* mod = m_mods[i];
		m_mods.erase(m_mods.begin() + i);
		delete mod;
	}
}

void ModLoader::loadMod(const std::string& name) {
	// Create a new mod object using the relative path "./mods/name/"
	Mod* mod = new Mod(name, "./mods/" + name + "/");
	// Add the object to the mods container
	m_mods.push_back(mod);
}

const std::vector<Mod*>& ModLoader::getMods() {
	// Return the mod object container
	return m_mods;
}

Mod* ModLoader::getModBySpawnerName(const std::string& name) {
	// Iterate through the mods
	for (Mod* mod : m_mods) {
		// Iterate through each mod's exported spawners
		for (std::string spawner : mod->getSpawners()) {
			// If the current spawner matches the given name return it
			if (spawner == name) return mod;
		}
	}
	// No mod was found that matches the spawner name, return nullptr
	return nullptr;
}

Mod* ModLoader::getModByPowerupName(const std::string& name) {
	// Iterate through the mods
	for (Mod* mod : m_mods) {
		// Iterate through each mod's exported powerups
		for (std::string powerup : mod->getPowerups()) {
			// If the current spawner matches the given name return it
			if (powerup == name) return mod;
		}
	}
	// No mod was found that matches the powerup name, return nullptr
	return nullptr;
}