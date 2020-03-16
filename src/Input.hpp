#ifndef INPUT_HPP
#define INPUT_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

class Input {
public:
	static void init(sol::state& config);

	static bool pressed(const std::string& action);

	static void registerKeys(sol::state& config);

private:
	static std::unordered_map<std::string, sf::Keyboard::Key> m_keybinds;

};

#endif /* INPUT_HPP */