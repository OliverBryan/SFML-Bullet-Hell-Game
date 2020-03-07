#ifndef MOD_LOADER_HPP
#define MOD_LOADER_HPP

#include <string>
#include <vector>
#include "Mod.hpp"

// Class used to load and store mods
class ModLoader {
public:
	ModLoader();
	~ModLoader();

	// Loads a mod with the specified name, using the relative path "./mods/name/"
	auto loadMod(const std::string& name) -> void;
	// Returns a vector containing the mod objects for all currently loaded mods
	auto getMods() -> std::vector<Mod*> const&;

	// Utility function to get a mod object by mod name (CURRENTLY UNIMPLEMENTED)
	auto getModByName(const std::string name) -> Mod* {}
	// Utility function to get a mod object with the name of one of its spawners
	auto getModBySpawnerName(const std::string& name) -> Mod*;
	// Utility function to get a mod object with the name of one of its power-ups
	auto getModByPowerupName(const std::string& name) -> Mod*;

private:
	// Internal storage container for mod objects
	std::vector<Mod*> m_mods;
};

#endif /* MOD_LOADER_HPP */