#ifndef MOD_LOADER_HPP
#define MOD_LOADER_HPP

#include <string>
#include <vector>
#include "Mod.hpp"

class ModLoader {
public:
	ModLoader();
	~ModLoader();

	void loadMod(const std::string& name, const std::string& path);
	std::vector<Mod*> getMods();

private:
	std::vector<Mod*> m_mods;
};

#endif /* MOD_LOADER_HPP */