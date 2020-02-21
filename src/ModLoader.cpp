#include "ModLoader.hpp"
#include <Windows.h>
#include <iostream>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

ModLoader::ModLoader() {}

ModLoader::~ModLoader() {
	for (int i = 0; i < m_mods.size(); i++) {
		Mod* mod = m_mods[i];
		m_mods.erase(m_mods.begin() + i);
		delete mod;
	}
}

void ModLoader::loadMod(const std::string& name) {
	Mod* mod = new Mod(name, "./mods/" + name + "/");
	m_mods.push_back(mod);
}

const std::vector<Mod*>& ModLoader::getMods() {
	return m_mods;
}

Mod* ModLoader::getModBySpawnerName(const std::string& name) {
	for (Mod* mod : m_mods) {
		for (std::string spawner : mod->getSpawners()) {
			if (spawner == name) return mod;
		}
	}
	return nullptr;
}

Mod* ModLoader::getModByPowerupName(const std::string& name) {
	for (Mod* mod : m_mods) {
		for (std::string powerup : mod->getPowerups()) {
			if (powerup == name) return mod;
		}
	}
	return nullptr;
}